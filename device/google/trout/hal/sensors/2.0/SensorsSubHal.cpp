/*
 * Copyright (C) 2020 The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
#define LOG_TAG "GoogleIIOSensorSubHal"

#include "SensorsSubHal.h"
#include <android/hardware/sensors/2.0/types.h>
#include <log/log.h>

ISensorsSubHal* sensorsHalGetSubHal(uint32_t* version) {
    static ::android::hardware::sensors::V2_0::subhal::implementation::SensorsSubHal subHal;
    *version = SUB_HAL_2_0_VERSION;
    return &subHal;
}

namespace android {
namespace hardware {
namespace sensors {
namespace V2_0 {
namespace subhal {
namespace implementation {

using ::android::hardware::Void;
using ::android::hardware::sensors::V1_0::Event;
using ::android::hardware::sensors::V1_0::RateLevel;
using ::android::hardware::sensors::V1_0::SharedMemInfo;
using ::android::hardware::sensors::V2_0::SensorTimeout;
using ::android::hardware::sensors::V2_0::WakeLockQueueFlagBits;
using ::android::hardware::sensors::V2_0::implementation::ScopedWakelock;
using ::sensor::hal::configuration::V1_0::Sensor;
using ::sensor::hal::configuration::V1_0::SensorHalConfiguration;

#define SENSOR_XML_CONFIG_FILE_NAME "sensor_hal_configuration.xml"
static const char* gSensorConfigLocationList[] = {"/odm/etc/sensors/", "/vendor/etc/sensors/"};
static const int gSensorConfigLocationListSize =
        (sizeof(gSensorConfigLocationList) / sizeof(gSensorConfigLocationList[0]));

#define MODULE_NAME "android.hardware.sensors@2.0-Google-IIO-Subhal"

static std::optional<std::vector<Sensor>> readSensorsConfigFromXml() {
    for (int i = 0; i < gSensorConfigLocationListSize; i++) {
        const auto sensor_config_file =
                std::string(gSensorConfigLocationList[i]) + SENSOR_XML_CONFIG_FILE_NAME;
        auto sensorConfig = ::sensor::hal::configuration::V1_0::read(sensor_config_file.c_str());
        if (sensorConfig) {
            auto modulesList = sensorConfig->getFirstModules()->get_module();
            for (auto module : modulesList) {
                if (module.getHalName().compare(MODULE_NAME) == 0) {
                    return module.getFirstSensors()->getSensor();
                }
            }
        }
    }
    ALOGI("Could not find the sensors configuration for module %s", MODULE_NAME);
    return std::nullopt;
}

static std::optional<std::vector<Configuration>> getSensorConfiguration(
        const std::vector<Sensor>& sensor_list, const std::string& name, SensorType type) {
    for (auto sensor : sensor_list) {
        if ((name.compare(sensor.getName()) == 0) && (type == (SensorType)sensor.getType())) {
            return sensor.getConfiguration();
        }
    }
    ALOGI("Could not find the sensor configuration for %s ", name.c_str());
    return std::nullopt;
}

static bool isSensorSupported(iio_device_data* sensor) {
#define SENSOR_SUPPORTED(SENSOR_NAME, SENSOR_TYPE) \
    { .name = SENSOR_NAME, .type = SENSOR_TYPE, }
    static const std::vector<sensors_supported_hal> supported_sensors = {
            SENSOR_SUPPORTED("scmi.iio.accel", SensorType::ACCELEROMETER),
            SENSOR_SUPPORTED("scmi.iio.gyro", SensorType::GYROSCOPE),
    };
#undef SENSOR_SUPPORTED

    if (!sensor) return false;

    auto iter = std::find_if(
            supported_sensors.begin(), supported_sensors.end(),
            [&sensor](const auto& candidate) -> bool { return candidate.name == sensor->name; });
    if (iter == supported_sensors.end()) return false;

    sensor->type = iter->type;
    return true;
}

SensorsSubHal::SensorsSubHal() : mCallback(nullptr), mNextHandle(1) {
    int err;
    std::vector<iio_device_data> iio_devices;
    const auto sensors_config_list = readSensorsConfigFromXml();
    err = load_iio_devices(DEFAULT_IIO_DIR, &iio_devices, isSensorSupported);
    if (err == 0) {
        for (auto& iio_device : iio_devices) {
            err = scan_elements(iio_device.sysfspath, &iio_device);
            if (err == 0) {
                err = enable_sensor(iio_device.sysfspath, false);
                if (err == 0) {
                    std::optional<std::vector<Configuration>> sensor_configuration = std::nullopt;
                    if (sensors_config_list)
                        sensor_configuration = getSensorConfiguration(
                                *sensors_config_list, iio_device.name, iio_device.type);

                    if (iio_device.channelInfo.size() == NUM_OF_CHANNEL_SUPPORTED) {
                        AddSensor(iio_device, sensor_configuration);
                    } else {
                        ALOGE("SensorsSubHal(): Unexpected number of channels for sensor %s",
                              iio_device.sysfspath.c_str());
                    }
                } else {
                    ALOGE("SensorsSubHal(): Error in enabling_sensor %s to %d error code %d",
                          iio_device.sysfspath.c_str(), false, err);
                }
            } else {
                ALOGE("SensorsSubHal(): Error in scanning channels for IIO device %s error code %d",
                      iio_device.sysfspath.c_str(), err);
            }
        }
    } else {
        ALOGE("SensorsSubHal: load_iio_devices returned error %d", err);
    }
}

// Methods from ::android::hardware::sensors::V2_0::ISensors follow.
Return<void> SensorsSubHal::getSensorsList(getSensorsList_cb _hidl_cb) {
    std::vector<SensorInfo> sensors;
    for (const auto& sensor : mSensors) {
        SensorInfo sensorInfo = sensor.second->getSensorInfo();
        sensorInfo.flags &= ~static_cast<uint32_t>(V1_0::SensorFlagBits::MASK_DIRECT_CHANNEL);
        sensorInfo.flags &= ~static_cast<uint32_t>(V1_0::SensorFlagBits::MASK_DIRECT_REPORT);
        sensors.push_back(sensorInfo);
    }

    _hidl_cb(sensors);
    return Void();
}

Return<Result> SensorsSubHal::setOperationMode(OperationMode mode) {
    for (auto& sensor : mSensors) {
        sensor.second->setOperationMode(mode);
    }
    mCurrentOperationMode = mode;
    return Result::OK;
}

Return<Result> SensorsSubHal::activate(int32_t sensorHandle, bool enabled) {
    auto sensor = mSensors.find(sensorHandle);
    if (sensor != mSensors.end()) {
        sensor->second->activate(enabled);
        return Result::OK;
    }
    return Result::BAD_VALUE;
}

Return<Result> SensorsSubHal::batch(int32_t sensorHandle, int64_t samplingPeriodNs,
                                    int64_t /* maxReportLatencyNs */) {
    auto sensor = mSensors.find(sensorHandle);
    if (sensor != mSensors.end()) {
        sensor->second->batch(samplingPeriodNs);
        return Result::OK;
    }
    return Result::BAD_VALUE;
}

Return<Result> SensorsSubHal::flush(int32_t sensorHandle) {
    auto sensor = mSensors.find(sensorHandle);
    if (sensor != mSensors.end()) {
        return sensor->second->flush();
    }
    return Result::BAD_VALUE;
}

Return<Result> SensorsSubHal::injectSensorData(const Event& /* event */) {
    return Result::INVALID_OPERATION;
}

Return<void> SensorsSubHal::registerDirectChannel(const SharedMemInfo& /* mem */,
                                                  registerDirectChannel_cb _hidl_cb) {
    _hidl_cb(Result::INVALID_OPERATION, -1 /* channelHandle */);
    return Return<void>();
}

Return<Result> SensorsSubHal::unregisterDirectChannel(int32_t /* channelHandle */) {
    return Result::INVALID_OPERATION;
}

Return<void> SensorsSubHal::configDirectReport(int32_t /* sensorHandle */,
                                               int32_t /* channelHandle */, RateLevel /* rate */,
                                               configDirectReport_cb _hidl_cb) {
    _hidl_cb(Result::INVALID_OPERATION, 0 /* reportToken */);
    return Return<void>();
}

Return<void> SensorsSubHal::debug(const hidl_handle& fd, const hidl_vec<hidl_string>& args) {
    if (fd.getNativeHandle() == nullptr || fd->numFds < 1) {
        ALOGE("%s: missing fd for writing", __FUNCTION__);
        return Void();
    }
    FILE* out = fdopen(dup(fd->data[0]), "w");

    if (args.size() != 0) {
        fprintf(out,
                "Note: sub-HAL %s currently does not support args. Input arguments are "
                "ignored.\n",
                getName().c_str());
    }

    std::ostringstream stream;
    stream << "Available sensors:" << std::endl;
    for (auto& sensor : mSensors) {
        SensorInfo info = sensor.second->getSensorInfo();
        HWSensorBase* hwSensor = static_cast<HWSensorBase*>(sensor.second.get());
        stream << "Name: " << info.name << std::endl;
        stream << "handle: " << info.sensorHandle << std::endl;
        stream << "resolution: " << info.resolution << " minDelay: " << info.minDelay
               << " maxDelay:" << info.maxDelay << std::endl;
        stream << "iio path" << hwSensor->mIioData.sysfspath << std::endl;
    }

    stream << std::endl;

    fprintf(out, "%s", stream.str().c_str());

    fclose(out);
    return Return<void>();
}

Return<Result> SensorsSubHal::initialize(const sp<IHalProxyCallback>& halProxyCallback) {
    mCallback = halProxyCallback;
    setOperationMode(OperationMode::NORMAL);
    return Result::OK;
}

void SensorsSubHal::postEvents(const std::vector<Event>& events, bool wakeup) {
    ScopedWakelock wakelock = mCallback->createScopedWakelock(wakeup);
    mCallback->postEvents(events, std::move(wakelock));
}
void SensorsSubHal::AddSensor(const struct iio_device_data& iio_data,
                              const std::optional<std::vector<Configuration>>& config) {
    HWSensorBase* sensor = HWSensorBase::buildSensor(mNextHandle++ /* sensorHandle */,
                                                     this /* callback */, iio_data, config);
    if (sensor != nullptr)
        mSensors[sensor->getSensorInfo().sensorHandle] = std::unique_ptr<SensorBase>(sensor);
    else
        ALOGE("Unable to add sensor %s as buildSensor returned null", iio_data.name.c_str());
}

}  // namespace implementation
}  // namespace subhal
}  // namespace V2_0
}  // namespace sensors
}  // namespace hardware
}  // namespace android

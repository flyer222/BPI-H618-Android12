package com.bigbigcloud.devicehive.api;


import com.bigbigcloud.devicehive.entity.Device;
import com.bigbigcloud.devicehive.entity.DeviceClass;
import com.bigbigcloud.devicehive.service.RestCallback;

import java.util.List;

/**
 * Client side controller for devices: <i>/device</i>. See <a href="http://www.devicehive.com/restful#Reference/Device">DeviceHive
 * RESTful API: Device</a> for details. and device classes: <i>device/class</i> See <a
 * href="http://www.devicehive.com/restful#Reference/DeviceClass">DeviceHive RESTful API: DeviceClass</a> for details.
 */
public interface DeviceController {

    //device block

    /**
     * Queries list of all available devices according to the specified parameters. See <a
     * href="http://www.devicehive.com/restful#Reference/Device/list"> DeviceHive RESTful API: Device: list</a> for more
     * details.
     *
     * @param name               Device name.
     * @param namePattern        Device name pattern.
     * @param status             Device status
     * @param networkId          Associated network identifier
     * @param networkName        Associated network name
     * @param deviceClassId      Associated device class identifier
     * @param deviceClassName    Associated device class name
     * @param deviceClassVersion Associated device class version
     * @param sortField          Result list sort field. Available values are "Name", "Status", "Network" and
     *                           "DeviceClass".
     * @param sortOrder          Result list sort order. Available values are ASC and DESC.
     * @param take               Number of records to take from the result list.
     * @param skip               Number of records to skip in the result list.
     * @return list of <a href="http://www.devicehive.com/restful#Reference/Device">Devices</a>
     */
    List<Device> listDevices(String name, String namePattern, String status, Long networkId, String networkName,
                             Integer deviceClassId, String deviceClassName, String deviceClassVersion,
                             String sortField, String sortOrder, Integer take, Integer skip);

    /**
     * Gets information about device. See <a href="http://www.devicehive.com/restful#Reference/Device/get">DeviceHive
     * RESTful API: Device: get</a> for more details.
     *
     * @param deviceId Device unique identifier
     * @return If successful, this method returns a <a href="http://www.devicehive.com/restful#Reference/Device">Device</a>
     *         resource in the response body.
     */
    Device getDevice(String deviceId) ;

    /**
     * Registers a device. If device with specified identifier has already been registered, it gets to be updated in
     * case when valid key is provided in the authorization header. See <a href="http://www.devicehive.com/restful#Reference/Device/register">DeviceHive
     * RESTful API: Device: register</a> for more details.
     *
     * @param device   In the request body, supply a Device resource. See <a href="http://www.devicehive
     *                 .com/restful#Reference/Device/register">
     */
    void registerDevice(Device device, RestCallback<String> restCallback);

    void syncDevice(Device device, RestCallback<String> restCallback);

    /**
     * Deletes an existing device. See <a href="http://www.devicehive.com/restful#Reference/Device/delete">DeviceHive
     * RESTful API: Device: delete</a>  for more details.
     *
     * @param deviceId Device unique identifier
     */
    void deleteDevice(String deviceId);


    //device class block

    /**
     * Gets list of device classes. See <a href="http://www.devicehive.com/restful#Reference/DeviceClass/list">DeviceHive
     * RESTful API: DeviceClass: list</a> for more details
     *
     * @param name        Device class name.
     * @param namePattern Device class name pattern.
     * @param version     Device class version.
     * @param sortField   Result list sort field. Available values are "ID" and "Name".
     * @param sortOrder   Result list sort order. Available values are ASC and DESC.
     * @param take        Number of records to take from the result list.
     * @param skip        Number of records to skip from the result list.
     * @return If successful, this method returns array of <a href="http://www.devicehive
     *         .com/restful#Reference/DeviceClass"> DeviceClass </a> resources in the response body.
     */
    List<DeviceClass> listDeviceClass(String name, String namePattern, String version, String sortField,
                                      String sortOrder, Integer take, Integer skip);

    /**
     * Gets information about device class and its equipment. Implementation of <a href="http://www.devicehive.com/restful#Reference/DeviceClass/get">DeviceHive
     * RESTful API: DeviceClass: get</a>
     *
     * @param classId device class identifier
     * @return If successful, this method returns a <a href="http://www.devicehive .com/restful#Reference/DeviceClass">DeviceClass</a>
     *         resource in the response body.
     */
    DeviceClass getDeviceClass(long classId);

    /**
     * Creates new device class. See <a href="http://www.devicehive.com/restful#Reference/DeviceClass/insert">DeviceHive
     * RESTful API: DeviceClass: insert</a> for more details.
     *
     * @param deviceClass device class to be inserted
     * @return device class identifier
     */
    long insertDeviceClass(DeviceClass deviceClass);

    /**
     * Updates an existing device class. See <a href="http://www.devicehive.com/restful#Reference/DeviceClass/update">DeviceHive
     * RESTful API: DeviceClass: update</a> for more details
     *
     * @param deviceClass device class to be updated
     */
    void updateDeviceClass(DeviceClass deviceClass);

    /**
     * Deletes an existing device class by id. See <a href="http://www.devicehive.com/restful#Reference/DeviceClass/delete">DeviceHive
     * RESTful API: DeviceClass: delete</a> for more details.
     *
     * @param classId device class identifier
     */
    void deleteDeviceClass(long classId);
}

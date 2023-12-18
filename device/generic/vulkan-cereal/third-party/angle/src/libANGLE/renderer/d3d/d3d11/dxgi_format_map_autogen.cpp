// GENERATED FILE - DO NOT EDIT.
// Generated by gen_dxgi_format_table.py using data from dxgi_format_data.json.
//
// Copyright 2020 The ANGLE Project Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.
//
// DXGI format info:
//   Determining metadata about a DXGI format.

#include "libANGLE/renderer/Format.h"

using namespace angle;

namespace rx
{

namespace d3d11
{

GLenum GetComponentType(DXGI_FORMAT dxgiFormat)
{
    switch (dxgiFormat)
    {
        case DXGI_FORMAT_420_OPAQUE:
            break;
        case DXGI_FORMAT_A8P8:
            break;
        case DXGI_FORMAT_A8_UNORM:
            return GL_UNSIGNED_NORMALIZED;
        case DXGI_FORMAT_AI44:
            break;
        case DXGI_FORMAT_AYUV:
            break;
        case DXGI_FORMAT_B4G4R4A4_UNORM:
            return GL_UNSIGNED_NORMALIZED;
        case DXGI_FORMAT_B5G5R5A1_UNORM:
            return GL_UNSIGNED_NORMALIZED;
        case DXGI_FORMAT_B5G6R5_UNORM:
            return GL_UNSIGNED_NORMALIZED;
        case DXGI_FORMAT_B8G8R8A8_TYPELESS:
            break;
        case DXGI_FORMAT_B8G8R8A8_UNORM:
            return GL_UNSIGNED_NORMALIZED;
        case DXGI_FORMAT_B8G8R8A8_UNORM_SRGB:
            return GL_UNSIGNED_NORMALIZED;
        case DXGI_FORMAT_B8G8R8X8_TYPELESS:
            break;
        case DXGI_FORMAT_B8G8R8X8_UNORM:
            return GL_UNSIGNED_NORMALIZED;
        case DXGI_FORMAT_B8G8R8X8_UNORM_SRGB:
            return GL_UNSIGNED_NORMALIZED;
        case DXGI_FORMAT_BC1_TYPELESS:
            break;
        case DXGI_FORMAT_BC1_UNORM:
            return GL_UNSIGNED_NORMALIZED;
        case DXGI_FORMAT_BC1_UNORM_SRGB:
            return GL_UNSIGNED_NORMALIZED;
        case DXGI_FORMAT_BC2_TYPELESS:
            break;
        case DXGI_FORMAT_BC2_UNORM:
            return GL_UNSIGNED_NORMALIZED;
        case DXGI_FORMAT_BC2_UNORM_SRGB:
            return GL_UNSIGNED_NORMALIZED;
        case DXGI_FORMAT_BC3_TYPELESS:
            break;
        case DXGI_FORMAT_BC3_UNORM:
            return GL_UNSIGNED_NORMALIZED;
        case DXGI_FORMAT_BC3_UNORM_SRGB:
            return GL_UNSIGNED_NORMALIZED;
        case DXGI_FORMAT_BC4_SNORM:
            return GL_SIGNED_NORMALIZED;
        case DXGI_FORMAT_BC4_TYPELESS:
            break;
        case DXGI_FORMAT_BC4_UNORM:
            return GL_UNSIGNED_NORMALIZED;
        case DXGI_FORMAT_BC5_SNORM:
            return GL_SIGNED_NORMALIZED;
        case DXGI_FORMAT_BC5_TYPELESS:
            break;
        case DXGI_FORMAT_BC5_UNORM:
            return GL_UNSIGNED_NORMALIZED;
        case DXGI_FORMAT_BC6H_SF16:
            break;
        case DXGI_FORMAT_BC6H_TYPELESS:
            break;
        case DXGI_FORMAT_BC6H_UF16:
            break;
        case DXGI_FORMAT_BC7_TYPELESS:
            break;
        case DXGI_FORMAT_BC7_UNORM:
            return GL_UNSIGNED_NORMALIZED;
        case DXGI_FORMAT_BC7_UNORM_SRGB:
            return GL_UNSIGNED_NORMALIZED;
        case DXGI_FORMAT_D16_UNORM:
            return GL_UNSIGNED_NORMALIZED;
        case DXGI_FORMAT_D24_UNORM_S8_UINT:
            break;
        case DXGI_FORMAT_D32_FLOAT:
            return GL_FLOAT;
        case DXGI_FORMAT_D32_FLOAT_S8X24_UINT:
            break;
        case DXGI_FORMAT_G8R8_G8B8_UNORM:
            return GL_UNSIGNED_NORMALIZED;
        case DXGI_FORMAT_IA44:
            break;
        case DXGI_FORMAT_NV11:
            break;
        case DXGI_FORMAT_NV12:
            break;
        case DXGI_FORMAT_P010:
            break;
        case DXGI_FORMAT_P016:
            break;
        case DXGI_FORMAT_P8:
            break;
        case DXGI_FORMAT_R10G10B10A2_TYPELESS:
            break;
        case DXGI_FORMAT_R10G10B10A2_UINT:
            return GL_UNSIGNED_INT;
        case DXGI_FORMAT_R10G10B10A2_UNORM:
            return GL_UNSIGNED_NORMALIZED;
        case DXGI_FORMAT_R10G10B10_XR_BIAS_A2_UNORM:
            return GL_UNSIGNED_NORMALIZED;
        case DXGI_FORMAT_R11G11B10_FLOAT:
            return GL_FLOAT;
        case DXGI_FORMAT_R16G16B16A16_FLOAT:
            return GL_FLOAT;
        case DXGI_FORMAT_R16G16B16A16_SINT:
            return GL_INT;
        case DXGI_FORMAT_R16G16B16A16_SNORM:
            return GL_SIGNED_NORMALIZED;
        case DXGI_FORMAT_R16G16B16A16_TYPELESS:
            break;
        case DXGI_FORMAT_R16G16B16A16_UINT:
            return GL_UNSIGNED_INT;
        case DXGI_FORMAT_R16G16B16A16_UNORM:
            return GL_UNSIGNED_NORMALIZED;
        case DXGI_FORMAT_R16G16_FLOAT:
            return GL_FLOAT;
        case DXGI_FORMAT_R16G16_SINT:
            return GL_INT;
        case DXGI_FORMAT_R16G16_SNORM:
            return GL_SIGNED_NORMALIZED;
        case DXGI_FORMAT_R16G16_TYPELESS:
            break;
        case DXGI_FORMAT_R16G16_UINT:
            return GL_UNSIGNED_INT;
        case DXGI_FORMAT_R16G16_UNORM:
            return GL_UNSIGNED_NORMALIZED;
        case DXGI_FORMAT_R16_FLOAT:
            return GL_FLOAT;
        case DXGI_FORMAT_R16_SINT:
            return GL_INT;
        case DXGI_FORMAT_R16_SNORM:
            return GL_SIGNED_NORMALIZED;
        case DXGI_FORMAT_R16_TYPELESS:
            break;
        case DXGI_FORMAT_R16_UINT:
            return GL_UNSIGNED_INT;
        case DXGI_FORMAT_R16_UNORM:
            return GL_UNSIGNED_NORMALIZED;
        case DXGI_FORMAT_R1_UNORM:
            return GL_UNSIGNED_NORMALIZED;
        case DXGI_FORMAT_R24G8_TYPELESS:
            break;
        case DXGI_FORMAT_R24_UNORM_X8_TYPELESS:
            return GL_UNSIGNED_NORMALIZED;
        case DXGI_FORMAT_R32G32B32A32_FLOAT:
            return GL_FLOAT;
        case DXGI_FORMAT_R32G32B32A32_SINT:
            return GL_INT;
        case DXGI_FORMAT_R32G32B32A32_TYPELESS:
            break;
        case DXGI_FORMAT_R32G32B32A32_UINT:
            return GL_UNSIGNED_INT;
        case DXGI_FORMAT_R32G32B32_FLOAT:
            return GL_FLOAT;
        case DXGI_FORMAT_R32G32B32_SINT:
            return GL_INT;
        case DXGI_FORMAT_R32G32B32_TYPELESS:
            break;
        case DXGI_FORMAT_R32G32B32_UINT:
            return GL_UNSIGNED_INT;
        case DXGI_FORMAT_R32G32_FLOAT:
            return GL_FLOAT;
        case DXGI_FORMAT_R32G32_SINT:
            return GL_INT;
        case DXGI_FORMAT_R32G32_TYPELESS:
            break;
        case DXGI_FORMAT_R32G32_UINT:
            return GL_UNSIGNED_INT;
        case DXGI_FORMAT_R32G8X24_TYPELESS:
            break;
        case DXGI_FORMAT_R32_FLOAT:
            return GL_FLOAT;
        case DXGI_FORMAT_R32_FLOAT_X8X24_TYPELESS:
            return GL_FLOAT;
        case DXGI_FORMAT_R32_SINT:
            return GL_INT;
        case DXGI_FORMAT_R32_TYPELESS:
            break;
        case DXGI_FORMAT_R32_UINT:
            return GL_UNSIGNED_INT;
        case DXGI_FORMAT_R8G8B8A8_SINT:
            return GL_INT;
        case DXGI_FORMAT_R8G8B8A8_SNORM:
            return GL_SIGNED_NORMALIZED;
        case DXGI_FORMAT_R8G8B8A8_TYPELESS:
            break;
        case DXGI_FORMAT_R8G8B8A8_UINT:
            return GL_UNSIGNED_INT;
        case DXGI_FORMAT_R8G8B8A8_UNORM:
            return GL_UNSIGNED_NORMALIZED;
        case DXGI_FORMAT_R8G8B8A8_UNORM_SRGB:
            return GL_UNSIGNED_NORMALIZED;
        case DXGI_FORMAT_R8G8_B8G8_UNORM:
            return GL_UNSIGNED_NORMALIZED;
        case DXGI_FORMAT_R8G8_SINT:
            return GL_INT;
        case DXGI_FORMAT_R8G8_SNORM:
            return GL_SIGNED_NORMALIZED;
        case DXGI_FORMAT_R8G8_TYPELESS:
            break;
        case DXGI_FORMAT_R8G8_UINT:
            return GL_UNSIGNED_INT;
        case DXGI_FORMAT_R8G8_UNORM:
            return GL_UNSIGNED_NORMALIZED;
        case DXGI_FORMAT_R8_SINT:
            return GL_INT;
        case DXGI_FORMAT_R8_SNORM:
            return GL_SIGNED_NORMALIZED;
        case DXGI_FORMAT_R8_TYPELESS:
            break;
        case DXGI_FORMAT_R8_UINT:
            return GL_UNSIGNED_INT;
        case DXGI_FORMAT_R8_UNORM:
            return GL_UNSIGNED_NORMALIZED;
        case DXGI_FORMAT_R9G9B9E5_SHAREDEXP:
            return GL_FLOAT;
        case DXGI_FORMAT_UNKNOWN:
            break;
        case DXGI_FORMAT_X24_TYPELESS_G8_UINT:
            return GL_UNSIGNED_INT;
        case DXGI_FORMAT_X32_TYPELESS_G8X24_UINT:
            return GL_UNSIGNED_INT;
        case DXGI_FORMAT_Y210:
            break;
        case DXGI_FORMAT_Y216:
            break;
        case DXGI_FORMAT_Y410:
            break;
        case DXGI_FORMAT_Y416:
            break;
        case DXGI_FORMAT_YUY2:
            break;
        default:
            break;
    }

    UNREACHABLE();
    return GL_NONE;
}

}  // namespace d3d11

namespace d3d11_angle
{

const Format &GetFormat(DXGI_FORMAT dxgiFormat)
{
    switch (dxgiFormat)
    {
        case DXGI_FORMAT_420_OPAQUE:
            break;
        case DXGI_FORMAT_A8P8:
            break;
        case DXGI_FORMAT_A8_UNORM:
            return Format::Get(FormatID::A8_UNORM);
        case DXGI_FORMAT_AI44:
            break;
        case DXGI_FORMAT_AYUV:
            break;
        case DXGI_FORMAT_B4G4R4A4_UNORM:
            return Format::Get(FormatID::B4G4R4A4_UNORM);
        case DXGI_FORMAT_B5G5R5A1_UNORM:
            return Format::Get(FormatID::B5G5R5A1_UNORM);
        case DXGI_FORMAT_B5G6R5_UNORM:
            return Format::Get(FormatID::B5G6R5_UNORM);
        case DXGI_FORMAT_B8G8R8A8_TYPELESS:
            return Format::Get(FormatID::B8G8R8A8_TYPELESS);
        case DXGI_FORMAT_B8G8R8A8_UNORM:
            return Format::Get(FormatID::B8G8R8A8_UNORM);
        case DXGI_FORMAT_B8G8R8A8_UNORM_SRGB:
            return Format::Get(FormatID::B8G8R8A8_UNORM_SRGB);
        case DXGI_FORMAT_B8G8R8X8_TYPELESS:
            break;
        case DXGI_FORMAT_B8G8R8X8_UNORM:
            return Format::Get(FormatID::B8G8R8X8_UNORM);
        case DXGI_FORMAT_B8G8R8X8_UNORM_SRGB:
            break;
        case DXGI_FORMAT_BC1_TYPELESS:
            break;
        case DXGI_FORMAT_BC1_UNORM:
            return Format::Get(FormatID::BC1_RGBA_UNORM_BLOCK);
        case DXGI_FORMAT_BC1_UNORM_SRGB:
            return Format::Get(FormatID::BC1_RGBA_UNORM_SRGB_BLOCK);
        case DXGI_FORMAT_BC2_TYPELESS:
            break;
        case DXGI_FORMAT_BC2_UNORM:
            return Format::Get(FormatID::BC2_RGBA_UNORM_BLOCK);
        case DXGI_FORMAT_BC2_UNORM_SRGB:
            return Format::Get(FormatID::BC2_RGBA_UNORM_SRGB_BLOCK);
        case DXGI_FORMAT_BC3_TYPELESS:
            break;
        case DXGI_FORMAT_BC3_UNORM:
            return Format::Get(FormatID::BC3_RGBA_UNORM_BLOCK);
        case DXGI_FORMAT_BC3_UNORM_SRGB:
            return Format::Get(FormatID::BC3_RGBA_UNORM_SRGB_BLOCK);
        case DXGI_FORMAT_BC4_SNORM:
            return Format::Get(FormatID::BC4_RED_SNORM_BLOCK);
        case DXGI_FORMAT_BC4_TYPELESS:
            break;
        case DXGI_FORMAT_BC4_UNORM:
            return Format::Get(FormatID::BC4_RED_UNORM_BLOCK);
        case DXGI_FORMAT_BC5_SNORM:
            return Format::Get(FormatID::BC5_RG_SNORM_BLOCK);
        case DXGI_FORMAT_BC5_TYPELESS:
            break;
        case DXGI_FORMAT_BC5_UNORM:
            return Format::Get(FormatID::BC5_RG_UNORM_BLOCK);
        case DXGI_FORMAT_BC6H_SF16:
            break;
        case DXGI_FORMAT_BC6H_TYPELESS:
            break;
        case DXGI_FORMAT_BC6H_UF16:
            break;
        case DXGI_FORMAT_BC7_TYPELESS:
            break;
        case DXGI_FORMAT_BC7_UNORM:
            break;
        case DXGI_FORMAT_BC7_UNORM_SRGB:
            break;
        case DXGI_FORMAT_D16_UNORM:
            return Format::Get(FormatID::D16_UNORM);
        case DXGI_FORMAT_D24_UNORM_S8_UINT:
            return Format::Get(FormatID::D24_UNORM_S8_UINT);
        case DXGI_FORMAT_D32_FLOAT:
            return Format::Get(FormatID::D32_FLOAT);
        case DXGI_FORMAT_D32_FLOAT_S8X24_UINT:
            return Format::Get(FormatID::D32_FLOAT_S8X24_UINT);
        case DXGI_FORMAT_G8R8_G8B8_UNORM:
            break;
        case DXGI_FORMAT_IA44:
            break;
        case DXGI_FORMAT_NV11:
            break;
        case DXGI_FORMAT_NV12:
            break;
        case DXGI_FORMAT_P010:
            break;
        case DXGI_FORMAT_P016:
            break;
        case DXGI_FORMAT_P8:
            break;
        case DXGI_FORMAT_R10G10B10A2_TYPELESS:
            break;
        case DXGI_FORMAT_R10G10B10A2_UINT:
            return Format::Get(FormatID::R10G10B10A2_UINT);
        case DXGI_FORMAT_R10G10B10A2_UNORM:
            return Format::Get(FormatID::R10G10B10A2_UNORM);
        case DXGI_FORMAT_R10G10B10_XR_BIAS_A2_UNORM:
            break;
        case DXGI_FORMAT_R11G11B10_FLOAT:
            return Format::Get(FormatID::R11G11B10_FLOAT);
        case DXGI_FORMAT_R16G16B16A16_FLOAT:
            return Format::Get(FormatID::R16G16B16A16_FLOAT);
        case DXGI_FORMAT_R16G16B16A16_SINT:
            return Format::Get(FormatID::R16G16B16A16_SINT);
        case DXGI_FORMAT_R16G16B16A16_SNORM:
            return Format::Get(FormatID::R16G16B16A16_SNORM);
        case DXGI_FORMAT_R16G16B16A16_TYPELESS:
            break;
        case DXGI_FORMAT_R16G16B16A16_UINT:
            return Format::Get(FormatID::R16G16B16A16_UINT);
        case DXGI_FORMAT_R16G16B16A16_UNORM:
            return Format::Get(FormatID::R16G16B16A16_UNORM);
        case DXGI_FORMAT_R16G16_FLOAT:
            return Format::Get(FormatID::R16G16_FLOAT);
        case DXGI_FORMAT_R16G16_SINT:
            return Format::Get(FormatID::R16G16_SINT);
        case DXGI_FORMAT_R16G16_SNORM:
            return Format::Get(FormatID::R16G16_SNORM);
        case DXGI_FORMAT_R16G16_TYPELESS:
            break;
        case DXGI_FORMAT_R16G16_UINT:
            return Format::Get(FormatID::R16G16_UINT);
        case DXGI_FORMAT_R16G16_UNORM:
            return Format::Get(FormatID::R16G16_UNORM);
        case DXGI_FORMAT_R16_FLOAT:
            return Format::Get(FormatID::R16_FLOAT);
        case DXGI_FORMAT_R16_SINT:
            return Format::Get(FormatID::R16_SINT);
        case DXGI_FORMAT_R16_SNORM:
            return Format::Get(FormatID::R16_SNORM);
        case DXGI_FORMAT_R16_TYPELESS:
            break;
        case DXGI_FORMAT_R16_UINT:
            return Format::Get(FormatID::R16_UINT);
        case DXGI_FORMAT_R16_UNORM:
            return Format::Get(FormatID::R16_UNORM);
        case DXGI_FORMAT_R1_UNORM:
            break;
        case DXGI_FORMAT_R24G8_TYPELESS:
            break;
        case DXGI_FORMAT_R24_UNORM_X8_TYPELESS:
            break;
        case DXGI_FORMAT_R32G32B32A32_FLOAT:
            return Format::Get(FormatID::R32G32B32A32_FLOAT);
        case DXGI_FORMAT_R32G32B32A32_SINT:
            return Format::Get(FormatID::R32G32B32A32_SINT);
        case DXGI_FORMAT_R32G32B32A32_TYPELESS:
            break;
        case DXGI_FORMAT_R32G32B32A32_UINT:
            return Format::Get(FormatID::R32G32B32A32_UINT);
        case DXGI_FORMAT_R32G32B32_FLOAT:
            return Format::Get(FormatID::R32G32B32_FLOAT);
        case DXGI_FORMAT_R32G32B32_SINT:
            return Format::Get(FormatID::R32G32B32_SINT);
        case DXGI_FORMAT_R32G32B32_TYPELESS:
            break;
        case DXGI_FORMAT_R32G32B32_UINT:
            return Format::Get(FormatID::R32G32B32_UINT);
        case DXGI_FORMAT_R32G32_FLOAT:
            return Format::Get(FormatID::R32G32_FLOAT);
        case DXGI_FORMAT_R32G32_SINT:
            return Format::Get(FormatID::R32G32_SINT);
        case DXGI_FORMAT_R32G32_TYPELESS:
            break;
        case DXGI_FORMAT_R32G32_UINT:
            return Format::Get(FormatID::R32G32_UINT);
        case DXGI_FORMAT_R32G8X24_TYPELESS:
            break;
        case DXGI_FORMAT_R32_FLOAT:
            return Format::Get(FormatID::R32_FLOAT);
        case DXGI_FORMAT_R32_FLOAT_X8X24_TYPELESS:
            break;
        case DXGI_FORMAT_R32_SINT:
            return Format::Get(FormatID::R32_SINT);
        case DXGI_FORMAT_R32_TYPELESS:
            break;
        case DXGI_FORMAT_R32_UINT:
            return Format::Get(FormatID::R32_UINT);
        case DXGI_FORMAT_R8G8B8A8_SINT:
            return Format::Get(FormatID::R8G8B8A8_SINT);
        case DXGI_FORMAT_R8G8B8A8_SNORM:
            return Format::Get(FormatID::R8G8B8A8_SNORM);
        case DXGI_FORMAT_R8G8B8A8_TYPELESS:
            return Format::Get(FormatID::R8G8B8A8_TYPELESS);
        case DXGI_FORMAT_R8G8B8A8_UINT:
            return Format::Get(FormatID::R8G8B8A8_UINT);
        case DXGI_FORMAT_R8G8B8A8_UNORM:
            return Format::Get(FormatID::R8G8B8A8_UNORM);
        case DXGI_FORMAT_R8G8B8A8_UNORM_SRGB:
            return Format::Get(FormatID::R8G8B8A8_UNORM_SRGB);
        case DXGI_FORMAT_R8G8_B8G8_UNORM:
            break;
        case DXGI_FORMAT_R8G8_SINT:
            return Format::Get(FormatID::R8G8_SINT);
        case DXGI_FORMAT_R8G8_SNORM:
            return Format::Get(FormatID::R8G8_SNORM);
        case DXGI_FORMAT_R8G8_TYPELESS:
            break;
        case DXGI_FORMAT_R8G8_UINT:
            return Format::Get(FormatID::R8G8_UINT);
        case DXGI_FORMAT_R8G8_UNORM:
            return Format::Get(FormatID::R8G8_UNORM);
        case DXGI_FORMAT_R8_SINT:
            return Format::Get(FormatID::R8_SINT);
        case DXGI_FORMAT_R8_SNORM:
            return Format::Get(FormatID::R8_SNORM);
        case DXGI_FORMAT_R8_TYPELESS:
            break;
        case DXGI_FORMAT_R8_UINT:
            return Format::Get(FormatID::R8_UINT);
        case DXGI_FORMAT_R8_UNORM:
            return Format::Get(FormatID::R8_UNORM);
        case DXGI_FORMAT_R9G9B9E5_SHAREDEXP:
            return Format::Get(FormatID::R9G9B9E5_SHAREDEXP);
        case DXGI_FORMAT_UNKNOWN:
            return Format::Get(FormatID::NONE);
        case DXGI_FORMAT_X24_TYPELESS_G8_UINT:
            break;
        case DXGI_FORMAT_X32_TYPELESS_G8X24_UINT:
            break;
        case DXGI_FORMAT_Y210:
            break;
        case DXGI_FORMAT_Y216:
            break;
        case DXGI_FORMAT_Y410:
            break;
        case DXGI_FORMAT_Y416:
            break;
        case DXGI_FORMAT_YUY2:
            break;
        default:
            break;
    }

    UNREACHABLE();
    return Format::Get(FormatID::NONE);
}

}  // namespace d3d11_angle

}  // namespace rx

#include "budCovCommon.hpp"
#include "budCovUtils.hpp"
#include "budCovPlatform.h"
#include "budCovDevice.h"
#include "budCovContext.h"

#ifdef __cplusplus
extern "C" {
#endif

CL_API_ENTRY cl_int CL_API_CALL
clGetPlatformIDs(cl_uint num_entries,
                 cl_platform_id* platforms,
                 cl_uint* num_platforms) CL_API_SUFFIX__VERSION_1_0
{
    if (num_entries == 0 && platforms) return CL_INVALID_VALUE;
    if (!platforms && !num_platforms) return CL_INVALID_VALUE;

    return cov::getPlatformIDs(num_entries, platforms, num_platforms);
}

CL_API_ENTRY cl_int CL_API_CALL
clGetPlatformInfo(cl_platform_id platform,
                  cl_platform_info param_name,
                  size_t param_value_size,
                  void* param_value,
                  size_t* param_value_size_ret) CL_API_SUFFIX__VERSION_1_0
{
    if (!platform || !cov::isValidObject<cov::Platform>(platform)) return CL_INVALID_PLATFORM;

    return cov::getPlatformInfo(platform, param_name, param_value_size, param_value, param_value_size_ret);
}

CL_API_ENTRY cl_int CL_API_CALL
clGetDeviceIDs(cl_platform_id platform,
               cl_device_type device_type,
               cl_uint num_entries,
               cl_device_id* devices,
               cl_uint* num_devices) CL_API_SUFFIX__VERSION_1_0
{
    if (!platform || !cov::isValidObject<cov::Platform>(platform)) return CL_INVALID_PLATFORM;
    if (device_type != CL_DEVICE_TYPE_ALL &&
        device_type != CL_DEVICE_TYPE_DEFAULT &&
        device_type != CL_DEVICE_TYPE_CPU &&
        device_type != CL_DEVICE_TYPE_GPU &&
        device_type != CL_DEVICE_TYPE_ACCELERATOR) return CL_INVALID_DEVICE_TYPE;
    if (num_entries == 0 && devices) return CL_INVALID_VALUE;
    if (!devices && !num_devices) return CL_INVALID_VALUE;
    // Support GPU only because vulkan only runs on GPU
    if (device_type == CL_DEVICE_TYPE_CPU || device_type == CL_DEVICE_TYPE_ACCELERATOR) return CL_DEVICE_NOT_FOUND;

    return cov::getDeviceIDs(platform, device_type, num_entries, devices, num_devices);
}


CL_API_ENTRY cl_context CL_API_CALL
clCreateContext(const cl_context_properties* properties,
                cl_uint num_devices,
                const cl_device_id* devices,
                void (CL_CALLBACK* pfn_notify)(const char* errinfo,
                                               const void* private_info,
                                               size_t cb,
                                               void* user_data),
                void* user_data,
                cl_int* errcode_ret) CL_API_SUFFIX__VERSION_1_0
{
    if (properties) {
        uint32_t i = 0;
        bool hasPlatformProperties = false;
        while (properties[i] != 0) {
            if (properties[i] == CL_CONTEXT_PLATFORM) {
                if (hasPlatformProperties) {
                    *errcode_ret = CL_INVALID_PROPERTY;
                    return nullptr;
                }
                if (!cov::isValidObject<cov::Platform>(reinterpret_cast<void*>(properties[i + 1]))) {
                    *errcode_ret = CL_INVALID_PLATFORM;
                    return nullptr;
                }
                hasPlatformProperties = true; // platform here not actually used
            } else {
                *errcode_ret = CL_INVALID_PROPERTY;
                return nullptr;
            }
            i += 2;
        }
    }
    if (!devices || num_devices == 0) {
        *errcode_ret = CL_INVALID_VALUE;
        return nullptr;
    }
    if (!pfn_notify && user_data) {
        *errcode_ret = CL_INVALID_VALUE;
        return nullptr;
    }
    for (cl_uint i = 0; i < num_devices; i++) {
        if (!cov::isValidObject<cov::Device>(devices[i])) {
            *errcode_ret = CL_INVALID_DEVICE;
            return nullptr;
        }
    }

    return cov::createContext(properties, num_devices, devices, pfn_notify, user_data, errcode_ret);
}

#ifdef __cplusplus
}
#endif

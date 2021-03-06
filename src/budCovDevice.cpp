#include "budCovDevice.h"

struct _cl_device_id {
    cov::Device m_device;
};

namespace cov {

extern Platform g_platform;
Device g_device{g_platform};

Device::Device(Platform& platform)
    : ClObject(),
      m_vkPhysicalDevice(platform.m_vkPhysicalDevice),
      m_vkQueueFamilyIndex(platform.m_vkQueueFamilyIndex)
{
    m_initSuccess = platform.m_initSuccess;
}

cl_int getDeviceIDs(cl_platform_id platform,
                    cl_device_type deviceType,
                    cl_uint numEntries,
                    cl_device_id* devices,
                    cl_uint* numDevices)
{
    auto p = reinterpret_cast<Platform*>(platform);
    if (numDevices) *numDevices = p->getNumDevices();
    if (!devices) return CL_SUCCESS;
    if (numEntries == 0) return CL_SUCCESS;

    if (!g_device.initSuccess()) return CL_OUT_OF_HOST_MEMORY;

    *devices = reinterpret_cast<_cl_device_id*>(&g_device);
    return CL_SUCCESS;
}

}

#pragma once

#include "budCovCommon.hpp"
#include "budCovObject.hpp"
#include "budCovUtils.hpp"
#include "budCovPlatform.h"

namespace cov {

class Device : public ClObject<ObjectMagic, ObjectMagic::DEVICE_MAGIC> {
    friend class Context;
public:
    explicit Device(Platform& platform);

private:
    VkPhysicalDevice m_vkPhysicalDevice;
    uint32_t m_vkQueueFamilyIndex;
};

cl_int getDeviceIDs(cl_platform_id platform,
                    cl_device_type deviceType,
                    cl_uint numEntries,
                    cl_device_id* devices,
                    cl_uint* numDevices);

}
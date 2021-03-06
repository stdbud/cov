#include "budCovPlatform.h"

struct _cl_platform_id {
    cov::Platform m_platform;
};

namespace cov {

Platform g_platform{};

Platform::Platform()
    : ClObject(),
      m_profile("EMBEDDED_PROFILE"),
      m_version("OpenCL 1.0"),
      m_name("cov"),
      m_vendor("bud"),
      m_extensions(" "),
      m_vkInstance(VK_NULL_HANDLE),
      m_vkPhysicalDevice(VK_NULL_HANDLE),
      m_vkQueueFamilyIndex(UINT32_MAX)
{
    VkInstanceCreateInfo createInfo{};
    createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
    m_initSuccess = m_initSuccess && vkCreateInstance(&createInfo, nullptr, &m_vkInstance) == VK_SUCCESS;

    uint32_t physicalDeviceCount;
    m_initSuccess = m_initSuccess &&
                    vkEnumeratePhysicalDevices(m_vkInstance, &physicalDeviceCount, nullptr) == VK_SUCCESS &&
                    physicalDeviceCount != 0;
    std::vector<VkPhysicalDevice> physicalDevices(physicalDeviceCount);
    m_initSuccess = m_initSuccess &&
                    vkEnumeratePhysicalDevices(m_vkInstance, &physicalDeviceCount, physicalDevices.data()) == VK_SUCCESS;
    for (auto physicalDevice : physicalDevices) {
        uint32_t queueFamilyCount;
        vkGetPhysicalDeviceQueueFamilyProperties(physicalDevice, &queueFamilyCount, nullptr);
        std::vector<VkQueueFamilyProperties> queueFamilies(queueFamilyCount);
        vkGetPhysicalDeviceQueueFamilyProperties(physicalDevice, &queueFamilyCount, queueFamilies.data());

        for (uint32_t i = 0; i < queueFamilyCount; i++) {
            if (queueFamilies[i].queueCount == 0) continue;
            if (queueFamilies[i].queueFlags & VK_QUEUE_COMPUTE_BIT &&
                queueFamilies[i].queueFlags & VK_QUEUE_TRANSFER_BIT &&
                queueFamilies[i].queueCount > 0) {
                m_vkPhysicalDevice = physicalDevice;
                m_vkQueueFamilyIndex = i;
                return;
            }
        }
    }

    m_initSuccess = false;
}

Platform::~Platform()
{
    if (m_vkInstance != VK_NULL_HANDLE) vkDestroyInstance(m_vkInstance, nullptr);
}

cl_int getPlatformIDs(cl_uint numEntries,
                      cl_platform_id* platforms,
                      cl_uint* numPlatforms)
{
    if (numPlatforms) *numPlatforms = 1;
    if (!platforms) return CL_SUCCESS;
    if (numEntries == 0) return CL_SUCCESS;

    if (!g_platform.initSuccess()) return CL_OUT_OF_HOST_MEMORY;

    *platforms = reinterpret_cast<_cl_platform_id*>(&g_platform);
    return CL_SUCCESS;
}

cl_int getPlatformInfo(cl_platform_id platform,
                       cl_platform_info paramName,
                       size_t paramValueSize,
                       void* paramValue,
                       size_t* paramValueSizeRet)
{
    auto p = reinterpret_cast<Platform*>(platform);
    switch (paramName) {
        case CL_PLATFORM_PROFILE:
            return utils::getStringParam(p->m_profile, paramValueSize, paramValue, paramValueSizeRet);
        case CL_PLATFORM_VERSION:
            return utils::getStringParam(p->m_version, paramValueSize, paramValue, paramValueSizeRet);
        case CL_PLATFORM_NAME:
            return utils::getStringParam(p->m_name, paramValueSize, paramValue, paramValueSizeRet);
        case CL_PLATFORM_VENDOR:
            return utils::getStringParam(p->m_vendor, paramValueSize, paramValue, paramValueSizeRet);
        case CL_PLATFORM_EXTENSIONS:
            return utils::getStringParam(p->m_extensions, paramValueSize, paramValue, paramValueSizeRet);
        default:
            return CL_INVALID_VALUE;
    }
}

}

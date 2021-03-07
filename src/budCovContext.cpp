#include "budCovContext.h"

struct _cl_context {
    cov::Context m_context;
};

namespace cov {

Context::Context(const Device& device, contextCallback pfnNotify, void* userData)
    : ClObject(),
      m_device(device),
      m_callback(pfnNotify),
      m_userData(userData),
      m_vkDevice(VK_NULL_HANDLE),
      m_vkQueue(VK_NULL_HANDLE)
{
    VkDeviceQueueCreateInfo queueCreateInfo{};
    queueCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
    queueCreateInfo.queueFamilyIndex = m_device.m_vkQueueFamilyIndex;
    queueCreateInfo.queueCount = 1;
    const float priority = 1.0f;
    queueCreateInfo.pQueuePriorities = &priority;

    VkDeviceCreateInfo deviceCreateInfo{};
    deviceCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
    deviceCreateInfo.queueCreateInfoCount = 1;
    deviceCreateInfo.pQueueCreateInfos = &queueCreateInfo;
    m_initSuccess = m_initSuccess &&
        vkCreateDevice(m_device.m_vkPhysicalDevice, &deviceCreateInfo, nullptr, &m_vkDevice) == VK_SUCCESS;

    if (m_initSuccess) {
        vkGetDeviceQueue(m_vkDevice, m_device.m_vkQueueFamilyIndex, 0, &m_vkQueue);
    } else {
        m_callback("failed to create context!", nullptr, 0, m_userData);
    }
}

Context::~Context()
{
    if (m_vkDevice != VK_NULL_HANDLE) vkDestroyDevice(m_vkDevice, nullptr);
}

cl_context createContext(const cl_context_properties* properties,
                         cl_uint numDevices,
                         const cl_device_id* devices,
                         contextCallback pfnNotify,
                         void* userData,
                         cl_int* errcodeRet)
{
    (void)properties; // current not used

    if (numDevices != 1) {
        // only support one device
        *errcodeRet = CL_DEVICE_NOT_AVAILABLE;
        return nullptr;
    }

    auto d = reinterpret_cast<const Device*>(devices[0]);
    auto context = new(std::nothrow) Countable<Context>(*d, pfnNotify, userData);
    if (!context) {
        *errcodeRet = CL_OUT_OF_HOST_MEMORY;
        return nullptr;
    }

    auto c = reinterpret_cast<Context*>(context);
    if (!c->initSuccess()) {
        c->release();
        *errcodeRet = CL_OUT_OF_RESOURCES;
        return nullptr;
    }

    *errcodeRet = CL_SUCCESS;
    return reinterpret_cast<_cl_context*>(c);
}

cl_int retainContext(cl_context context)
{
    auto c = reinterpret_cast<Context*>(context);
    c->retain();
    return CL_SUCCESS;
}

cl_int releaseContext(cl_context context)
{
    auto c = reinterpret_cast<Context*>(context);
    c->release();
    return CL_SUCCESS;
}

}

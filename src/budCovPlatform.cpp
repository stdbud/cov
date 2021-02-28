#include "budCovPlatform.h"

struct _cl_platform_id {
    cov::IcdDispatch* m_icdTable = cov::getIcdTable();
    std::shared_ptr<cov::Platform> m_platform = std::make_shared<cov::Platform>();
};

_cl_platform_id g_platform{};

namespace cov {

Platform::Platform()
    : ClObject(),
      m_profile("EMBEDDED_PROFILE"),
      m_version("OpenCL 1.0"),
      m_name("cov"),
      m_vendor("bud"),
      m_extensions(" ")
{
    VkInstanceCreateInfo createInfo{};
    createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
    m_vkRes = vkCreateInstance(&createInfo, nullptr, &m_vkInstance);
}

Platform::~Platform()
{
    if (m_vkRes == VK_SUCCESS) vkDestroyInstance(m_vkInstance, nullptr);
}

cl_int Platform::getInitResult() const
{
    if (m_vkRes == VK_SUCCESS) return CL_SUCCESS;
    return CL_OUT_OF_HOST_MEMORY;
}

cl_int getPlatformIDs(cl_uint numEntries,
                      cl_platform_id* platforms,
                      cl_uint* numPlatforms)
{
    if (numPlatforms) *numPlatforms = 1;
    if (!platforms) return CL_SUCCESS;
    if (numEntries == 0) return CL_SUCCESS;

    auto p = castObjectPointer<Platform>(&g_platform);
    cl_int err = p->getInitResult();
    if (err != CL_SUCCESS) return err;

    *platforms = &g_platform;
    return CL_SUCCESS;
}

cl_int getPlatformInfo(cl_platform_id platform,
                       cl_platform_info paramName,
                       size_t paramValueSize,
                       void* paramValue,
                       size_t* paramValueSizeRet)
{
    auto p = castObjectPointer<Platform>(platform);
    switch (paramName) {
        case CL_PLATFORM_PROFILE:
            return getStringParam(p->m_profile, paramValueSize, paramValue, paramValueSizeRet);
        case CL_PLATFORM_VERSION:
            return getStringParam(p->m_version, paramValueSize, paramValue, paramValueSizeRet);
        case CL_PLATFORM_NAME:
            return getStringParam(p->m_name, paramValueSize, paramValue, paramValueSizeRet);
        case CL_PLATFORM_VENDOR:
            return getStringParam(p->m_vendor, paramValueSize, paramValue, paramValueSizeRet);
        case CL_PLATFORM_EXTENSIONS:
            return getStringParam(p->m_extensions, paramValueSize, paramValue, paramValueSizeRet);
        default:
            return CL_INVALID_VALUE;
    }
}

}

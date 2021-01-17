#pragma once

#include "clvk_common.hpp"
#include "clvk_object.hpp"
#include "clvk_utils.hpp"

namespace clvk {

class Platform : public ClObject, RefCounter<Platform> {
public:
    Platform();
    ~Platform();

    cl_int getInitResult() const;

    const std::string m_profile;
    const std::string m_version;
    const std::string m_name;
    const std::string m_vendor;
    const std::string m_extensions;
private:
    VkInstance m_vkInstance;
    VkResult m_vkRes;
};

cl_int getPlatformIDs(cl_uint numEntries,
                      cl_platform_id* platforms,
                      cl_uint* numPlatforms);

cl_int getPlatformInfo(cl_platform_id platform,
                       cl_platform_info param_name,
                       size_t param_value_size,
                       void* param_value,
                       size_t* param_value_size_ret);

}

struct _cl_platform_id {
    clvk::Platform platform;
};

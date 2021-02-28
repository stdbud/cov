#pragma once

#include "budCovCommon.hpp"
#include "budCovObject.hpp"
#include "budCovUtils.hpp"
#include "budCovIcd.h"

namespace cov {

class Platform : public ClObject<ObjectMagic, ObjectMagic::PLATFORM_MAGIC> {
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
                       cl_platform_info paramName,
                       size_t paramValueSize,
                       void* paramValue,
                       size_t* paramValueSizeRet);

}

#pragma once

#include "clvk_common.hpp"
#include "clvk_object.hpp"

namespace clvk {

class Platform : public ClObject, RefCounter<Platform> {
public:
    Platform();
private:
};

cl_int getPlatformIDs(cl_uint numEntries,
                      cl_platform_id* platforms,
                      cl_uint* numPlatforms);

}

struct _cl_platform_id {
    clvk::Platform platform;
};

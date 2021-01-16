#include "clvk_platform.hpp"
using namespace clvk;

Platform::Platform()
    : ClObject(),
      RefCounter() {}

cl_int getPlatformIDs(cl_uint numEntries,
                      cl_platform_id* platforms,
                      cl_uint* numPlatforms)
{
    if (numPlatforms) *numPlatforms = 1;
    if (!platforms) return CL_SUCCESS;
    if (numEntries == 0) return CL_SUCCESS;

    auto platform = new(std::nothrow) Platform();
    if (!platform) return CL_OUT_OF_HOST_MEMORY;

    *platforms = castObjectPointer<_cl_platform_id*>(platform);
}

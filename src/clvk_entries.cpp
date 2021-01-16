#include "clvk_common.hpp"
#include "clvk_platform.hpp"

#ifdef __cplusplus
extern "C" {
#endif

CL_API_ENTRY cl_int CL_API_CALL
clGetPlatformIDs(cl_uint num_entries,
                 cl_platform_id* platforms,
                 cl_uint* num_platforms) CL_API_SUFFIX__VERSION_1_0
{
    if (num_entries == 0 && !platforms) return CL_INVALID_VALUE;
    if (!platforms && !num_platforms) return CL_INVALID_VALUE;

    return clvk::getPlatformIDs(num_entries, platforms, num_platforms);
}

#ifdef __cplusplus
}
#endif

#include "budCovCommon.hpp"
#include "budCovPlatform.h"

#ifdef __cplusplus
extern "C" {
#endif

CL_API_ENTRY cl_int CL_API_CALL
clGetPlatformIDs(cl_uint num_entries,
                 cl_platform_id* platforms,
                 cl_uint* num_platforms) CL_API_SUFFIX__VERSION_1_0
{
    if (num_entries == 0 && platforms) return CL_INVALID_VALUE;
    if (!platforms && !num_platforms) return CL_INVALID_VALUE;

    return cov::getPlatformIDs(num_entries, platforms, num_platforms);
}

CL_API_ENTRY cl_int CL_API_CALL
clGetPlatformInfo(cl_platform_id platform,
                  cl_platform_info param_name,
                  size_t param_value_size,
                  void* param_value,
                  size_t* param_value_size_ret) CL_API_SUFFIX__VERSION_1_0
{
    if (!platform || !cov::isValidObject<cov::Platform>(platform)) return CL_INVALID_PLATFORM;

    return cov::getPlatformInfo(platform, param_name, param_value_size, param_value, param_value_size_ret);
}

#ifdef __cplusplus
}
#endif

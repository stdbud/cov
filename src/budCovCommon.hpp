#pragma once

#if (COV_MAX_VERSION == 120)
#define CL_TARGET_OPENCL_VERSION 120
#define CL_USE_DEPRECATED_OPENCL_1_0_APIS
#define CL_USE_DEPRECATED_OPENCL_1_1_APIS
#endif

#include <CL/cl.h>
#include <CL/cl_icd.h>

#include <vulkan/vulkan.h>

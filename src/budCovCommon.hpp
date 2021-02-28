#pragma once

#if (COV_MAX_VERSION == 100)
#define CL_TARGET_OPENCL_VERSION 100
#endif

#include <CL/cl.h>
#include <CL/cl_icd.h>

#include <vulkan/vulkan.h>

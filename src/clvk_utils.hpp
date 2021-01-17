#pragma once

#include <cstdio>
#include <cstdint>
#include <unordered_map>
#include <string>

namespace clvk {

#define printInfo printf
#define printError printf

inline cl_int getStringParam(const std::string& param,
                             size_t paramValueSize,
                             void* paramValue,
                             size_t* paramValueSizeRet)
{
    if (paramValueSizeRet) *paramValueSizeRet = param.size();
    if (paramValue) {
        if (paramValueSize < param.size()) return CL_INVALID_VALUE;
        param.copy(static_cast<char*>(paramValue), param.size());
    }
    return CL_SUCCESS;
}

}

#pragma once

#include <string>
#include <stdexcept>

template<typename ErrType, ErrType expected>
inline void checkErr(ErrType got, const std::string& message)
{
    if (got != expected) throw std::runtime_error(message);
}

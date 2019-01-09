#pragma once

#include <limits>

template <typename Type>
inline Type defaultValue()
{
    return Type();
}

template <>
inline double defaultValue()
{
    return std::numeric_limits<double>::quiet_NaN();
}

template <>
inline int defaultValue()
{
    return 0;
}

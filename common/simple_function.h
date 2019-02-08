#pragma once

#include "default_value.h"

#include <QMetaType>
#include <QVariant>

using SimpleFunction = std::function<void ()>;

Q_DECLARE_METATYPE(SimpleFunction)

template <>
inline SimpleFunction defaultValue()
{
    return nullptr;
}

inline QVariant toVariant(SimpleFunction function)
{
    return QVariant::fromValue(function);
}

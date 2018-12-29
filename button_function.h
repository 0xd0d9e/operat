#pragma once

#include "default_value.h"

#include <QMetaType>
#include <QVariant>

using ButtonFunction = std::function<void ()>;

Q_DECLARE_METATYPE(ButtonFunction)

template <>
inline ButtonFunction defaultValue()
{
    return nullptr;
}

inline QVariant toVariant(ButtonFunction function)
{
    return QVariant::fromValue(function);
}

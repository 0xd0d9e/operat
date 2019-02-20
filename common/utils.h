#pragma once

#include <QRectF>
#include <QTransform>

#include <cmath>

inline QRectF makeRect(const double width, const double height)
{
    return QRectF(-width/2.0, -height/2.0, width, height);
}
inline QRectF makeRect(const QPointF& center, const double width, const double height)
{
    return QRectF(center.x() - width/2.0, center.y() - height/2.0, width, height);
}
inline QRectF makeRect(const QPointF& center, const QSizeF& size)
{
    return makeRect(center, size.width(), size.height());
}

inline double calcMinScale(const QTransform& t)
{
    const double a = t.m11();
    const double b = t.m21();
    const double c = t.m12();
    const double d = t.m22();
    const double scaleX = sqrt(a*a + c*c);
    const double scaleY = sqrt(b*b + d*d);
    return std::min(scaleX, scaleY);
}

inline bool testFlag(const int flags, const int flag)
{
    return flags & flag;
}

inline void setFlag(int& flags, const int flag, const bool enabled)
{
    if (enabled == testFlag(flags, flag))
        return;

    if (enabled)
        flags |= flag;
    else
        flags ^= flag;
}

inline void addFlag(int& flags, const int flag)
{
    setFlag(flags, flag, true);
}

#pragma once

#include <QPointF>

#include <cmath>

inline double getLength(const QPointF& vec)
{
    return hypot(vec.x(), vec.y());
}

inline double getDistance(const QPointF& p1, const QPointF& p2)
{
    const QPointF diff = p2 - p1;
    return getLength(diff);
}

inline double getAngle(const QPointF& vec)
{
    return atan2(vec.y(), vec.x());
}

inline double getAngle(const QPointF& p1, const QPointF& p2)
{
    const QPointF diff = p2 - p1;
    return getAngle(diff);
}



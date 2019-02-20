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

inline QPointF getDirection(const double angle)
{
    return QPointF(cos(angle), sin(angle));
}

inline QPointF turnCw(const QPointF& dir)
{
    return QPointF(dir.y(), -dir.x());
}

inline QPointF turnCcw(const QPointF& dir)
{
    return QPointF(-dir.y(), dir.x());
}

inline double toDegree(const double radian)
{
    return radian * 180.0/M_PI;
}

const double angle2pi = M_PI * 2.0;

inline double angleDiff(const double max, const double min)
{
    if (max < min)
        return angleDiff(min, max);

    const double diff = max - min;
    return (diff > M_PI) ? min + angle2pi - max
                         : diff;
}

inline double normalizeAngle(double angle)
{
    while (angle < 0.0)
        angle += angle2pi;
    while (angle >= angle2pi)
        angle -= angle2pi;
    return angle;
}

inline double getAngle(const QPointF& vec)
{
    return normalizeAngle(atan2(vec.y(), vec.x()));
}

inline double getAngle(const QPointF& p1, const QPointF& p2)
{
    const QPointF diff = p2 - p1;
    return getAngle(diff);
}


/// Возвращает true если точка \a x0, \a y0 лежит на отрезке \a x1 \a y1, \a x2 \a y2
/*inline bool segmentContains(const double x1, const double y1,
                            const double x2, const double y2,
                            const double x0, const double y0)
{
    return qFuzzyCompare((x0 - x1) / (x2 - x1), (y0 - y1) / (y2 - y1));
}*/

/// Возвращает true если точка \a p0 лежит на отрезке \a p1, \a p2
inline bool segmentContains(const QPointF& p1, const QPointF& p2, const QPointF& p0)
{
    const double length = getDistance(p1, p2);
    return getDistance(p1, p0) < length
        && getDistance(p2, p0) < length;

    //return segmentContains(p1.x(), p1.y(), p2.x(), p2.y(), p0.x(), p0.y());
}

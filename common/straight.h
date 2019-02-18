#pragma once

#include <QPointF>
#include <limits>

/// Прямая заданная по точке и угловому коэффициенту
struct Straight
{
    //m
    double k = std::numeric_limits<double>::quiet_NaN();

    //k
    double b = std::numeric_limits<double>::quiet_NaN();

    /// return x by point
    inline double xAt(const double x, const double y) const
    {
        return (x + k * y - k * b) / (k * k + 1);
    }

    /// return y by x
    inline double yAt(const double x) const
    {
        return k * x + b;
    }

    /// return point on straight
    inline QPointF pointAt(const double x0, const double y0) const
    {
        const double x = xAt(x0, y0);
        return QPointF(x, yAt(x));
    }
    inline QPointF pointAt(const QPointF& pos) const
    {
        return pointAt(pos.x(), pos.y());
    }

    /// \name Уравнение прямой с угловым коэффициентом
    inline static Straight fromLine(const double x1, const double y1, const double x2, const double y2)
    {
        Straight s;
        s.k = (y2 - y1)/(x2 - x1);
        s.b = (x2 * y1 - x1 * y2) / (x2 - x1);
        return s;
    }
    inline static Straight fromLine(const QPointF& p1, const QPointF& p2)
    {
        return fromLine(p1.x(), p1.y(), p2.x(), p2.y());
    }
    ///@}
};


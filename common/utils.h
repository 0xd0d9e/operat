#pragma once

#include <QRectF>

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

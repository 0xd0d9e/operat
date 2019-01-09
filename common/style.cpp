#include "style.h"

#include <QPainter>

Style::Style(const QPen& pen, const QBrush& brush)
    : pen(pen)
    , brush(brush)
{
}

Style::Style(const QBrush& brush, const QPen& pen)
    : pen(pen)
    , brush(brush)
{
}

QPen Style::getPen() const
{
    return pen;
}

void Style::setPen(const QPen& value)
{
    pen = value;
}

QBrush Style::getBrush() const
{
    return brush;
}

void Style::setBrush(const QBrush& value)
{
    brush = value;
}

void Style::apply(QPainter* painter)
{
    painter->setPen(pen);
    painter->setBrush(brush);
}

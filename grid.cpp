#include "grid.h"

#include "debug.h"
#include "gridmetrics.h"

#include <QDebug>

int getIndexSize(const int index)
{
    if (index == 0)
        return 4;

    if (!(index % 5))
        return 2;

    return 0;
}

Grid::Grid(Component* parent, const QString& name, const QVariantMap& properties) : Shape(parent, name, properties)
{

}

bool Grid::contains(const QRectF& sceneRect) const
{
    if (getRect().isNull())
        return true;
    return Shape::contains(sceneRect);
}

void Grid::paintComponent(QPainter* painter, const QRectF& sceneRect)
{
    const QRectF rect = getRect();
    const QRectF targetRect = rect.isNull()
            ? sceneRect
            : rect.intersected(sceneRect);

    Shape::paintComponent(painter, sceneRect);


    const GridMetrics metrics(getSize());
    const int leftIndex = metrics.floor(targetRect.x());
    const int topIndex = metrics.floor(targetRect.y());
    const int gridWidth = metrics.ceil(targetRect.width()) + 1;
    const int gridHeight = metrics.ceil(targetRect.height()) + 1;

    const double left = metrics.unmap(leftIndex);
    const double top = metrics.unmap(topIndex);
    const double right = left + metrics.unmap(gridWidth);
    const double bottom = top + metrics.unmap(gridHeight);

    const QColor color = getPen().color();

    for (int gridX = 0; gridX < gridWidth; ++gridX)
    {
        const int gridIndex = leftIndex + gridX;
        const double x = metrics.unmap(gridIndex);
        const int size = getIndexSize(gridIndex);
        painter->setPen(QPen(color, size));
        painter->drawLine(x, top, x, bottom);
        if (size > 0)
        {
            painter->drawText(x + 5, sceneRect.bottom(), QString::number(x));
        }
    }
    for (int gridY = 0; gridY < gridHeight; ++gridY)
    {
        const int gridIndex = topIndex + gridY;
        const double y = metrics.unmap(gridIndex);
        const int size = getIndexSize(gridIndex);
        painter->setPen(QPen(color, size));
        painter->drawLine(left, y, right, y);
        if (size > 0)
        {
            painter->drawText(sceneRect.left(), y - 1, QString::number(y));
        }
    }
}
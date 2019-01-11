#include "grid.h"

#include "common/debug.h"
#include "common/grid_metrics.h"
#include "common/utils.h"

#include <QDebug>

inline int getIndexSize(const int index)
{
    if (index == 0)
        return 4;

    if (!(index % 5))
        return 2;

    return 0;
}

bool Grid::contains(const QRectF& sceneRect) const
{
    const QRectF rect = getRect();
    return rect.isNull() || rect.intersects(sceneRect);
}

void Grid::paintComponent(QPainter* painter, const QRectF& sceneRect)
{
    const QRectF rect = getRect();
    const QRectF targetRect = rect.isNull()
            ? sceneRect
            : rect.intersected(sceneRect);

    const double scale = std::max(1.0, floor(1.0 / calcMinScale(painter->transform())));
    const GridMetrics metrics(getSize() * scale);
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

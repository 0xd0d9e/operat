#include "route.h"

#include "common/geometry_math.h"

void Route::addPoint(const QPointF& pos, const double width, const double speed)
{
    if (points.empty())
        points.reserve(150);

    Point point;
    point.pos = pos;
    point.index = points.size();
    point.width = width;
    point.speed = speed;
    points.push_back(point);

    if (points.size() > 1)
    {
        const Point& start = points[point.index - 1];
        const Point& end = points.back();
        Segment segment;
        segment.boundingRect = QRectF(start.pos, end.pos);
        segment.index = point.index - 1;
        segment.length = getDistance(start.pos, end.pos);
        segment.straight = Straight::fromLine(start.pos, end.pos);
        segment.speed = start.speed;
        segments.push_back(segment);
    }
}

bool Route::contains(const QRectF& sceneRect) const
{
    for (const Segment& segment : segments)
    {
        if (segment.boundingRect.intersects(sceneRect))
            return true;
    }
    return false;
}

void Route::paintComponent(QPainter* painter, const QRectF& sceneRect)
{
    Component::paintComponent(painter, sceneRect);


    for (const Segment& segment : segments)
    {
        getLineStyle().apply(painter);

        painter->drawLine(points[segment.index].pos, points[segment.index + 1].pos);

        painter->setPen(QPen(Qt::red, 0, Qt::DotLine));
        painter->setBrush(Qt::NoBrush);
        painter->drawRect(segment.boundingRect);
    }

    const double radius = getPointRadius();
    const QPointF offset(radius, radius);


    const size_t lastPoint = points.size() - 1;
    for (const Point& point : points)
    {
        /// draw route width
        if (point.index != 0 && point.index != lastPoint)
        {
            painter->setPen(QPen(Qt::black, 0));
            painter->setBrush(Qt::NoBrush);
            const QPointF halfSize(point.width, point.width);
            painter->drawEllipse(QRectF(point.pos - halfSize, point.pos + halfSize));
        }

        getPointStyle().apply(painter);
        /// draw route point
        painter->drawEllipse(QRectF(point.pos - offset, point.pos + offset));
    }
}

const Route::Point& Route::getPoint(const int index) const
{
    return points[index];
}

const Route::Segment&Route::getSegment(const int index) const
{
    return segments[index];
}

int Route::getPointCount() const
{
    return points.size();
}

const std::vector<Route::Point>& Route::getPoints() const
{
    return points;
}

const std::vector<Route::Segment>& Route::getSegments() const
{
    return segments;
}

#include "route.h"

#include "common/geometry_math.h"

inline double calcStartTurningDistance(const double turnAngle, const double turningRadius)
{
    // Длина между точкой начала циркуляции и до точки пересечения плеч.
    return turningRadius * tan(turnAngle / 2.0);
}

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
        const QPointF diff = end.pos - start.pos;
        segment.length = getLength(diff);
        segment.dir = diff / segment.length;
        segment.inPointL = start.pos + turnCcw(segment.dir) * start.width;
        segment.inPointR = start.pos + turnCw(segment.dir) * start.width;
        segment.outPointL = end.pos + turnCcw(segment.dir) * end.width;
        segment.outPointR = end.pos + turnCw(segment.dir) * end.width;

        segment.straight = Straight::fromLine(start.pos, end.pos);
        segment.speed = start.speed;
        segment.angle = getAngle(start.pos, end.pos);

        if (!segments.empty())
        {
            Segment& prevSegment = segments.back();

            prevSegment.turnAngle = angleDiff(prevSegment.angle, segment.angle);
            prevSegment.circulationDistance = calcStartTurningDistance(prevSegment.turnAngle, start.turningRadius);
            prevSegment.turnDistance = prevSegment.circulationDistance + start.turnDeadDistance;
            prevSegment.turnPoint = start.pos - prevSegment.dir * (prevSegment.turnDistance);
            prevSegment.circulationPoint = start.pos - prevSegment.dir * (prevSegment.circulationDistance);
            prevSegment.turnStraight = segment.straight.parallel(prevSegment.turnPoint);
        }
        segments.push_back(segment);
    }
}

void Route::clearPoints()
{
    points.clear();
    segments.clear();
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

        if (!segment.turnPoint.isNull())
        {
            painter->setPen(QPen(QColor("#aaaaffaa"), 3));
            painter->setBrush(Qt::NoBrush);
            painter->drawPoint(segment.turnPoint);
        }
        if (!segment.circulationPoint.isNull())
        {
            painter->setPen(QPen(QColor("#aaaaffaa"), 3));
            painter->setBrush(Qt::NoBrush);
            painter->drawPoint(segment.circulationPoint);
        }

        painter->setPen(QPen(Qt::red, 1, Qt::DashLine));
        painter->drawLine(segment.outPointL, segment.inPointL);
        painter->drawLine(segment.outPointR, segment.inPointR);

    }

    const double radius = getPointRadius();
    const QPointF offset(radius, radius);


    const size_t lastPoint = points.size() - 1;
    for (const Point& point : points)
    {
        /// draw route width
        if (point.index != 0 && point.index != lastPoint)
        {
            painter->setPen(QPen(Qt::black, 1));
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

int Route::getSegmentCount() const
{
    return segments.size();
}

const std::vector<Route::Point>& Route::getPoints() const
{
    return points;
}

const std::vector<Route::Segment>& Route::getSegments() const
{
    return segments;
}

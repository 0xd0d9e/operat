#pragma once

#include <common/straight.h>
#include <common/style.h>
#include <components/component.h>

class Route : public Component
{
public:
    struct Point
    {
        QPointF pos;
        size_t index;
        double width;
        double speed;
        double turningRadius = 50.0;
    };
    struct Segment
    {
        size_t index;
        QRectF boundingRect;
        Straight straight;

        /// Направляющий вектор
        QPointF dir;
        /// Длина
        double length;

        double speed;
        /// направление сегмента (в радианах)
        double angle;

        /// Расстояние до начала входа в циркуляцию
        double turnDistance;
        /// Точка входа в циркуляцию
        QPointF turnPoint;
        /// Прямая параллельная след сегменту, проходящая через точку входа в циркуляцию
        Straight turnStraight;

        QPointF inPointL;
        QPointF inPointR;
        QPointF outPointL;
        QPointF outPointR;
    };

    DECLARE_CONSTRUCTOR(Route, Component)

    DECLARE_PROPERTY(Style, lineStyle, LineStyle)
    DECLARE_PROPERTY(Style, pointStyle, PointStyle)
    DECLARE_PROPERTY_D(double, pointRadius, PointRadius, 5.0)

    void addPoint(const QPointF& pos, const double width, const double speed);
    void clearPoints();

    /// component api
    bool contains(const QRectF& sceneRect) const override;
    void paintComponent(QPainter* painter, const QRectF& sceneRect) override;

    const Point& getPoint(const int index) const;
    const Segment& getSegment(const int index) const;

    int getPointCount() const;
    int getSegmentCount() const;

    const std::vector<Point>& getPoints() const;
    const std::vector<Segment>& getSegments() const;

private:
    std::vector<Point> points;
    std::vector<Segment> segments;
};

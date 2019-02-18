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
    };
    struct Segment
    {
        size_t index;
        QRectF boundingRect;
        QPointF wolPoint;
        Straight straight;
        double length;
        double speed;
    };

    DECLARE_CONSTRUCTOR(Route, Component)

    DECLARE_PROPERTY(Style, lineStyle, LineStyle)
    DECLARE_PROPERTY(Style, pointStyle, PointStyle)
    DECLARE_PROPERTY_D(double, pointRadius, PointRadius, 5.0)

    void addPoint(const QPointF& pos, const double width, const double speed);

    /// component api
    bool contains(const QRectF& sceneRect) const override;
    void paintComponent(QPainter* painter, const QRectF& sceneRect) override;

    const Point& getPoint(const int index) const;
    const Segment& getSegment(const int index) const;

    int getPointCount() const;

    const std::vector<Point>& getPoints() const;
    const std::vector<Segment>& getSegments() const;

private:
    std::vector<Point> points;
    std::vector<Segment> segments;
};

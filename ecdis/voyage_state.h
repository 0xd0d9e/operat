#pragma once

#include <QPointF>

class Route;

struct VoyageState
{
    QPointF pos;
    double course = 0.0;
    Route* route = nullptr;

    int currentPointIndex = -1;

    int nearPointIndex = -1;
    double nearPointDistance;

    /// Положение на траверзе
    QPointF traversePos;

    double traverseDistance;
};

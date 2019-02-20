#pragma once

#include "voyage_state.h"
#include "route.h"

class RouteCalculator
{
public:
    enum Flags
    {
        NoFlags = 0,

        OnRoute = 1,    ///< Судно в пределах корридора маршрута
        EndOfRoute = 2, ///< Маршрут завершен
        OnTraverse = 4  ///< Судно на траверзе маршрута
    };

    RouteCalculator(const Route& route, const VoyageState& state);

    int getCurrentPointIndex() const;
    QPointF getTraversePos() const;
    int getFlags() const;

    void updateCurrentPoint();

private:
    void updateOnRoute();


    /// Находит ближайшую к судну точку
    void findNearPoint(int& index, double& minDistance) const;

    /// Возвращает индекс заданной точки, если разница между курсом судна и направлением на нее
    /// находиться в створе +/- Pi/2 относительно курса судна.
    /// Иначе возвращает индекс соседней точки, ближайшей по направлению к курсу судна
    int findPointOnCourse(const int pointIndex) const;

    /// Возвращает разницу между курсом судна и направлением на заданную точку
    double findCourseDiff(const int pointIndex) const;

    /// Расчитывает ближайшую точку к судну на прямой заданного сигмента,
    /// возвращает true если точка находиться на сегменте
    bool calcTraversePoint(const int segmentIndex, QPointF& pos) const;

private:
    const Route& route;
    const VoyageState& state;

    /// Индекс текущей точки
    int currentPointIndex = -1;

    /// Индекс ближайшей точки
    int nearPointIndex = -1;

    /// Расстояние до ближайшей точки
    double nearPointDistance;

    /// Положение на траверзе
    QPointF traversePos;

    /// Дистанция от проекции положения коробля на сегменте маршрута до дальней точки сегмента
    double traverseDistance;

    /// Отклонение положение коробля от текущего сегмента маршрута
    double deviation;

    /// Признаки
    int flags = NoFlags;
};


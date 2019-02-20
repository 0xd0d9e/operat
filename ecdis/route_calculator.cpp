#include "route_calculator.h"

#include "route.h"

#include <common/geometry_math.h>
#include <common/straight.h>
#include <common/utils.h>

RouteCalculator::RouteCalculator(const Route& route, const VoyageState& state)
    : route(route)
    , state(state)
{
}

int RouteCalculator::getCurrentPointIndex() const
{
    return currentPointIndex;
}

QPointF RouteCalculator::getTraversePos() const
{
    return traversePos;
}

int RouteCalculator::getFlags() const
{
    return flags;
}

void RouteCalculator::updateCurrentPoint()
{
    /// Если в маршруте менее 2х точек, выходим
    if (route.getSegmentCount() < 1)
        return;

    /// Если был достигнут конец маршрута, то выходим
    if (testFlag(flags, EndOfRoute))
        return;

    /// Ищем ближайшую точку
    findNearPoint(nearPointIndex, nearPointDistance);

    /// Если мы находимся в районе первой точки маршрута
    if (nearPointIndex == 0)
    {
        /// проверяем находимся ли мы на первом сегменте
        const bool onTraverse = calcTraversePoint(nearPointIndex, traversePos);
        setFlag(flags, OnTraverse, onTraverse);

        if (onTraverse)
        {
            /// Если находимся на сегменте, то переключаемся на следующий
            currentPointIndex = std::max(nearPointIndex + 1, currentPointIndex);
        }
        /// если это не первый запуск алгоритма, то меняем точку на первую, так как
        /// даже если мы уплыли обратно за первую точку, то вести всеравно должны в следующую
        else if (currentPointIndex < 0)
        {
            /// Если нет, то значит мы еще не доехали до начала маршрута
            currentPointIndex = 0;
        }
    }
    /// Если мы находимся в районе последней точки
    else if (nearPointIndex == route.getSegmentCount())
    {
        /// проверяем, находимся ли мы на последнем участке
        const bool onTraverse = calcTraversePoint(nearPointIndex - 1, traversePos);
        setFlag(flags, OnTraverse, onTraverse);
        if (onTraverse)
        {
            /// Если находимся, то следуем в последнюю точку
            currentPointIndex = nearPointIndex;
        }
        else
        {
            /// Если мы уже достигли последней точки, то устанавливаем соотв призpнак
            flags = EndOfRoute;
            currentPointIndex = -1;
        }
    }
    /// Если мы находимся между первой и последней точкой
    else
    {
        /// Определяем, лежит ли ближайшая точка в "своре" курса, если нет,
        /// то пытаемся выбрать ближайшую по направлению к "створу" курса
        const int nextPointIndex = findPointOnCourse(nearPointIndex);

        /// Задаем ближайшую к створу точку как следующую, если она "старше" чем текущая
        if (nextPointIndex > currentPointIndex || currentPointIndex < 0)
            currentPointIndex = nextPointIndex;

        /// Определяем току траверза
        const bool onTraverse = calcTraversePoint(std::max(currentPointIndex - 1, 0), traversePos);
        setFlag(flags, OnTraverse, onTraverse);
    }

    /// Если мы находимся на траверзе
    if (testFlag(flags, OnTraverse))
    {
        /// Расчитываем отклонение от линии маршрута
        deviation = getDistance(traversePos, state.pos);

        const bool onRoute = deviation <= route.getPoint(currentPointIndex).width;
        setFlag(flags, OnRoute, onRoute);

        if (currentPointIndex < route.getSegmentCount())
        {
            const Route::Segment& currentSegment = route.getSegment(currentPointIndex - 1);
            const Route::Segment& nextSegment = route.getSegment(currentPointIndex);
            const QPointF nextSegmentPos = nextSegment.straight.pointAt(state.pos);
            const double nextSegmentDistance = getDistance(state.pos, nextSegmentPos);

            /// Если растояние до неалейной линии меньше чем расстояние
            /// от след сегмента до входа в точку входа в циркуляцию
            /// то переключаемся на следующий сегмент
            if (nextSegmentDistance < currentSegment.turnDistance)
            {
                ++currentPointIndex;
            }
        }
    }
}

void RouteCalculator::findNearPoint(int& index, double& minDistance) const
{
    index = -1;

    for (const Route::Point& point : route.getPoints())
    {
        const double currentDistance = getDistance(point.pos, state.pos);
        if (index < 0 || currentDistance < minDistance)
        {
            index = point.index;
            minDistance = currentDistance;
        }
    }
}

int RouteCalculator::findPointOnCourse(const int pointIndex) const
{
    /// В режиме "Ведение до ближайшей точки маршрута", выбор текущей ПТ должен осуществляться
    /// исходя из условий: дистанция до ПТ наименьшая, курсовой угол менее 90о
    /// в случае, если такая точка отсутствует (КУ>90о), то выбирается ПТ, курсовой угол на которую
    /// минимальный
    const double nearCourseDiff = findCourseDiff(pointIndex);

    int pointOnCourse = -1;

    if (fabs(nearCourseDiff) <= M_PI_2)
    {
        pointOnCourse = pointIndex;
    }
    else
    {
        const double nextCourseDiff = findCourseDiff(pointIndex + 1);
        const double prevCourseDiff = findCourseDiff(pointIndex - 1);

        if (fabs(nextCourseDiff) < fabs(prevCourseDiff))
        {
            pointOnCourse = pointIndex + 1;
        }
        else
        {
            pointOnCourse = pointIndex - 1;
        }
    }
    return pointOnCourse;
}

double RouteCalculator::findCourseDiff(const int pointIndex) const
{
    const double course = getAngle(state.pos, route.getPoint(pointIndex).pos);
    return angleDiff(course, state.course);
}

bool RouteCalculator::calcTraversePoint(const int segmentIndex, QPointF& pos) const
{
    Q_ASSERT(segmentIndex >= 0 && segmentIndex < route.getSegmentCount());

    const Route::Segment& segment = route.getSegment(segmentIndex);
    pos = segment.straight.pointAt(state.pos);

    return segmentContains(route.getPoint(segmentIndex).pos,
                           route.getPoint(segmentIndex + 1).pos,
                           pos);
}

#include "route_calculator.h"

#include "route.h"

#include <common/geometry_math.h>
#include <common/straight.h>

RouteCalculator::RouteCalculator(VoyageState& state) : state(state)
{

}

void RouteCalculator::findTargetPoint()
{
    findNearPoint();

    if (state.nearPointIndex < 0 || state.route->getPointCount() < 2)
        return;

    int segmentIndex = -1;
    if (state.nearPointIndex == 0)
    {
        segmentIndex = state.nearPointIndex;

        const Route::Segment& segment = state.route->getSegment(segmentIndex);

        state.traversePos = segment.straight.pointAt(state.pos);
        state.traverseDistance = getDistance(state.traversePos, state.route->getPoint(segmentIndex + 1).pos);

        if (state.traverseDistance < segment.length)
        {
            state.currentPointIndex = state.nearPointIndex + 1;
        }
        else
        {
            state.currentPointIndex = 0;
        }
    }
    else if (state.nearPointIndex == state.route->getPointCount() - 1)
    {
        segmentIndex = state.nearPointIndex - 1;
        const Route::Segment& segment = state.route->getSegment(segmentIndex);

        state.traversePos = segment.straight.pointAt(state.pos);
        state.traverseDistance = getDistance(state.traversePos, state.route->getPoint(segmentIndex).pos);

        if (state.traverseDistance < segment.length)
        {
            state.currentPointIndex = state.nearPointIndex;
        }
        else
        {
            state.currentPointIndex = -1;
        }
    }
    else
    {
        //TODO: detect by course
        segmentIndex = state.nearPointIndex;
        //const double nearPointCourse = getAngle(state.pos, nearPointPos);
    }

    qDebug("* findTargetPoint");
    qDebug("  nearPointIndex %d", state.nearPointIndex);
    qDebug("  currentPointIndex %d", state.currentPointIndex);
    qDebug("  segmentIndex %d", segmentIndex);
    qDebug() << "  state.pos", state.pos);
}

void RouteCalculator::findNearPoint()
{
    state.nearPointIndex = -1;

    for (const Route::Point& point : state.route->getPoints())
    {
        const double currentDistance = getDistance(point.pos, state.pos);
        if (state.nearPointIndex < 0 || currentDistance < state.nearPointDistance)
        {
            state.nearPointIndex = point.index;
            state.nearPointDistance = currentDistance;
        }
    }
}

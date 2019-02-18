#include "route_monitor.h"

#include "route.h"

#include <components/line.h>

void RouteMonitor::setRoute(Route* newRoute)
{
    route = newRoute;
}

void RouteMonitor::setShip(Component* newShip)
{
    ship = newShip;
}

void RouteMonitor::update(const double time)
{
    Q_UNUSED(time);

    if (getEnabled())
    {
        if (!ship || !state.route)
            return;

        state.pos = ship->getPos();
        state.course = ship->getRotation();

        calculator->findTargetPoint();

        traverseLine->setP1(state.pos);
        traverseLine->setP2(state.traversePos);

        if (state.currentPointIndex >= 0)
        {
            targetLine->setVisible(true);
            targetLine->setP1(state.pos);
            targetLine->setP2(route->getPoint(state.currentPointIndex).pos);
        }
        else
        {
            targetLine->setVisible(false);
        }
    }
}

void RouteMonitor::init()
{
    Component::init();

    calculator = new RouteCalculator(state);

    traverseLine = create<Line>("traverse", {{"pen", QPen(Qt::gray, 2, Qt::DotLine)}});
    traverseLine->setVisible(false);

    targetLine = create<Line>("target", {{"pen", QPen(QColor("#33aa33"), 2, Qt::DotLine)}});
}

void RouteMonitor::initilizeVoyage()
{
    if (!ship || !state.route)
        return;


    state = VoyageState();
    state.route = route;
    state.pos = ship->getPos();
    state.course = ship->getRotation();

    traverseLine->setVisible(true);
}

void RouteMonitor::onEnabledChanged(const bool enabled)
{
    if (enabled)
    {
        initilizeVoyage();
    }
}


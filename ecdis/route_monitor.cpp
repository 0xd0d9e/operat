#include "route_monitor.h"

#include "route.h"

#include <components/line.h>
#include <components/label.h>

inline QString calculatorFlagsToString(const int flags)
{
    QStringList names;
    if (flags & RouteCalculator::EndOfRoute)
        names << "EndOfRoute";
    if (flags & RouteCalculator::OnTraverse)
        names << "OnTraverse";
    if (flags & RouteCalculator::OnRoute)
        names << "OnRoute";
    return names.empty() ? QString("NoFlags")
                         : names.join("|");
}

inline QString calculatorReasonToString(const int flags)
{
    QStringList names;
    if (flags & RouteCalculator::NearFirstPointReason)
        names << "NearFirstPointReason";
    if (flags & RouteCalculator::NearCoursePointReason)
        names << "NearCoursePointReason";
    if (flags & RouteCalculator::NearLastPointReason)
        names << "NearLastPointReason";
    if (flags & RouteCalculator::NoMorePointsReason)
        names << "NoMorePointsReason";
    if (flags & RouteCalculator::CrossWolReason)
        names << "CrossWolReason";
    return names.empty() ? QString("Unexpected reason %1").arg(flags)
                         : names.join("|");
}

void RouteMonitor::setRoute(Route* newRoute)
{
    route = newRoute;
}

void RouteMonitor::setShip(Component* newShip)
{
    ship = newShip;
}

void RouteMonitor::resetState()
{
    if (!ship || !route)
        return;

    state = VoyageState();
    state.pos = ship->getPos();
    state.course = ship->getRotation();

    calculator = new RouteCalculator(*route, state);

    traverseLine->setVisible(true);
}

void RouteMonitor::update(const double time)
{
    Q_UNUSED(time);


    if (!getEnabled())
        return;

    if (!ship || !route)
        return;

    state.pos = ship->getPos();
    state.course = ship->getRotation();

    calculator->updateCurrentPoint();

    const int currentPointIndex = calculator->getCurrentPointIndex();

    if (currentPointIndex >= 0)
    {
        traverseLine->setP1(state.pos);
        traverseLine->setP2(calculator->getTraversePos());
        traverseLine->setVisible(true);

        if (!(calculator->getFlags() & RouteCalculator::OnTraverse))
        {
            addTraverseLine->setP1(calculator->getTraversePos());
            addTraverseLine->setP2(route->getPoint(currentPointIndex).pos);
            addTraverseLine->setVisible(true);
        }
        else
        {
            addTraverseLine->setVisible(false);
        }
    }
    else
    {
        traverseLine->setVisible(false);
    }

    if (currentPointIndex > 0 && currentPointIndex < route->getPointCount())
    {
        const Route::Segment& segment = route->getSegment(currentPointIndex - 1);
        nextTurnLine->setP1(segment.turnStraight.pointAt(state.pos));
        nextTurnLine->setP2(segment.turnStraight.pointAt(route->getPoint(currentPointIndex + 1).pos));
        nextTurnLine->setVisible(true);

        turnLine->setP1(state.pos);
        turnLine->setP2(segment.turnStraight.pointAt(state.pos));
        turnLine->setVisible(true);
    }
    else
    {
        turnLine->setVisible(false);
        nextTurnLine->setVisible(false);
    }

    if (currentPointIndex >= 0)
    {
        targetLine->setVisible(true);
        targetLine->setP1(state.pos);
        targetLine->setP2(route->getPoint(currentPointIndex).pos);
    }
    else
    {
        targetLine->setVisible(false);
    }

    QStringList lines;
    lines << QString("currentPointIndex %1").arg(currentPointIndex);
    lines << QString("flags %1").arg(calculatorFlagsToString(calculator->getFlags()));

    lines << "History:";
    for (const auto& pair : calculator->getCurrentPointIndexHistory())
    {
        lines << "  " + QString::number(pair.first) + ": " + calculatorReasonToString(pair.second);
    }
    textLabel->setText(lines.join("\n"));
}

void RouteMonitor::setupUi(Component* ui)
{
    textLabel = ui->create<Label>("text", {{"pos", QPointF(10, 200)},
                                           {"margin", 5.0},
                                           {"style", Style(QPen(Qt::black), QBrush(QColor("#88aaaaff")))},
                                           {"type", Shape::Rectangle}});
}

void RouteMonitor::init()
{
    Component::init();

    addTraverseLine = create<Line>("addTraverseLine", {{"pen", QPen(Qt::gray, 1, Qt::DotLine)}});
    addTraverseLine->setVisible(false);
    traverseLine = create<Line>("traverse", {{"pen", QPen(Qt::gray, 1, Qt::DotLine)}});
    traverseLine->setVisible(false);

    targetLine = create<Line>("target", {{"pen", QPen(QColor("#33aa33"), 2, Qt::DotLine)}});

    nextTurnLine = create<Line>("nextTurnLine", {{"pen", QPen(QColor("#3333aa"), 1, Qt::DotLine)}});
    nextTurnLine->setVisible(false);
    turnLine = create<Line>("turnLine", {{"pen", QPen(QColor("#3333aa"), 1, Qt::DotLine)}});
}

void RouteMonitor::onEnabledChanged(const bool enabled)
{
    if (enabled)
    {
        resetState();
    }
}


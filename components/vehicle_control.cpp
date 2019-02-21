#include "vehicle_control.h"

#include "common/debug.h"
#include "common/utils.h"
#include "common/geometry_math.h"
#include "events/key_event.h"

#include <QPropertyAnimation>

#include <cmath>

void VehicleControl::setTarget(Component* newTarget)
{
    target = newTarget;
}

bool VehicleControl::keyPress(KeyEvent* event)
{
    keys.insert(event->getKey());
    return false;
}

bool VehicleControl::keyRelease(KeyEvent* event)
{
    keys.remove(event->getKey());
    return false;
}

void VehicleControl::update(const double time)
{
    if (!target)
        return;

    switch (getMode())
    {

    case SimpleMoving:
        simpleMoving(time);
        break;

    case DirectionalMoving:
        directionalMoving(time);
        break;

    default:
        qDebug("Invalid mode");
        break;

    }
}

void VehicleControl::simpleMoving(const double time)
{
    QPointF vec;
    if (keys.contains(Qt::Key_W))
        vec.setY(-1);
    else if (keys.contains(Qt::Key_S))
        vec.setY(1);
    if (keys.contains(Qt::Key_A))
        vec.setX(-1);
    else if (keys.contains(Qt::Key_D))
        vec.setX(1);

    if (!vec.isNull())
    {
        const double speed = getSpeed();
        const QPointF offset(vec.x() * speed * time,
                             vec.y() * speed * time);
        target->setPos(target->getPos() + offset);
    }
}

void VehicleControl::directionalMoving(const double time)
{
    double force = std::numeric_limits<double>::quiet_NaN();
    if (keys.contains(Qt::Key_W))
        force = getSpeed();
    else if (keys.contains(Qt::Key_S))
        force = -getSpeed();

    double rotation = std::numeric_limits<double>::quiet_NaN();
    if (keys.contains(Qt::Key_A))
        rotation = -getRotationSpeed();
    else if (keys.contains(Qt::Key_D))
        rotation = getRotationSpeed();

    if (!std::isnan(rotation))
        target->setRotation(normalizeAngle(target->getRotation() + rotation * time));

    if (!std::isnan(force))
    {
        const QPointF dir = getDirection(target->getRotation());
        target->setPos(target->getPos() + dir * force * time);
    }
}

#include "vehicle_control.h"

#include "common/debug.h"
#include "common/utils.h"
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

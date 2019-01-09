#include "wheel_event.h"

#include <QWheelEvent>

WheelEvent::WheelEvent(QWheelEvent* event, const QPointF& scenePos)
    : Event(Event::Wheel)
    , delta(event->delta())
    , scenePos(scenePos)
{
}

int WheelEvent::getDelta() const
{
    return delta;
}

QPointF WheelEvent::getScenePos() const
{
    return scenePos;
}

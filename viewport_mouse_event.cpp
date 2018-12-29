#include "viewport_mouse_event.h"

#include <QMouseEvent>

ViewportMouseEvent::ViewportMouseEvent(QMouseEvent* event, const QPointF& scenePos)
    : scenePos(scenePos)
    , event(event)
{
}

QPointF ViewportMouseEvent::getViewportPos() const
{
    return event->localPos();
}

QPointF ViewportMouseEvent::getScenePos() const
{
    return scenePos;
}

int ViewportMouseEvent::getButton() const
{
    return event->button();
}

int ViewportMouseEvent::getButtons() const
{
    return event->buttons();
}

int ViewportMouseEvent::getModifiers() const
{
    return event->modifiers();
}

#include "mouse_event.h"

#include <QMouseEvent>

MouseEvent::MouseEvent(QMouseEvent* event, const QPointF& scenePos)
    : Event(event)
    , viewportPos(event->localPos())
    , scenePos(scenePos)
    , button(event->button())
    , buttons(event->buttons())
    , modifiers(event->modifiers())
{
}

QPointF MouseEvent::getViewportPos() const
{
    return viewportPos;
}

QPointF MouseEvent::getScenePos() const
{
    return scenePos;
}

int MouseEvent::getButton() const
{
    return button;
}

int MouseEvent::getButtons() const
{
    return buttons;
}

int MouseEvent::getModifiers() const
{
    return modifiers;
}

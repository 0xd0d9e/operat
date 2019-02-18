#include "button.h"

#include "common/debug.h"
#include "events/mouse_event.h"

void Button::paintComponent(QPainter* painter, const QRectF& sceneRect)
{
    switch (getState())
    {
    case NormalState:
        setStyle(getNormalStyle());
        break;
    case PressedState:
        setStyle(getPressedStyle());
        break;
    case HighlightState:
        setStyle(getHighlightStyle());
        break;
    }

    Label::paintComponent(painter, sceneRect);
}

bool Button::mousePress(MouseEvent* event)
{
    if (event->getButton() != Qt::LeftButton)
        return false;

    if (!contains(QRectF(event->getScenePos(), QSizeF(1.0, 1.0))))
        return false;

    setState(PressedState);
    pressed = true;
    return false;
}


bool Button::mouseMove(MouseEvent* event)
{
    if (!pressed)
    {
        const bool hover = contains(QRectF(event->getScenePos(), QSizeF(1.0, 1.0)));
        setState(hover ? HighlightState : NormalState);
    }
    return false;
}

bool Button::mouseRelease(MouseEvent* event)
{
    if (event->getButton() != Qt::LeftButton)
        return false;

    if (pressed && contains(QRectF(event->getScenePos(), QSizeF(1.0, 1.0))))
    {
        if (getFunction())
            getFunction()();
        pressed = false;
        setState(NormalState);
    }
    return false;
}

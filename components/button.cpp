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

void Button::mousePress(MouseEvent* event)
{
    if (event->getButton() != Qt::LeftButton)
        return;

    if (!contains(QRectF(event->getScenePos(), QSizeF(1.0, 1.0))))
        return;

    setState(PressedState);
    pressed = true;
}


void Button::mouseMove(MouseEvent* event)
{
    if (!pressed)
    {
        const bool hover = contains(QRectF(event->getScenePos(), QSizeF(1.0, 1.0)));
        setState(hover ? HighlightState : NormalState);
    }
}

void Button::mouseRelease(MouseEvent* event)
{
    if (event->getButton() != Qt::LeftButton)
        return;

    if (getFunction() && pressed && contains(QRectF(event->getScenePos(), QSizeF(1.0, 1.0))))
        getFunction()();

    pressed = false;
    setState(NormalState);
}

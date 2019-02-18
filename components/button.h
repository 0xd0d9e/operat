#pragma once

#include "common/simple_function.h"
#include "events/event_listener.h"
#include "label.h"

class MouseEvent;

class Button : public Label, public EventListener
{
public:
    enum State
    {
        NormalState,
        PressedState,
        HighlightState
    };
    DECLARE_CONSTRUCTOR(Button, Label)

    DECLARE_PROPERTY(SimpleFunction, function, Function)
    DECLARE_PROPERTY_D(int, state, State, NormalState)

    DECLARE_PROPERTY(Style, normalStyle, NormalStyle)
    DECLARE_PROPERTY(Style, pressedStyle, PressedStyle)
    DECLARE_PROPERTY(Style, highlightStyle, HighlightStyle)

    void paintComponent(QPainter *painter, const QRectF &sceneRect) override;

    DECLARE_PREPARE_EVENT(Label)

    bool mousePress(MouseEvent *event) override;
    bool mouseMove(MouseEvent *event) override;
    bool mouseRelease(MouseEvent *event) override;

private:
    bool pressed = false;
    QPointF pos;
};

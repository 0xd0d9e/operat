#pragma once

#include "button_function.h"
#include "label.h"

class MenuButton : public Label
{
public:
    enum State
    {
        NormalState,
        PressedState,
        HighlightState
    };
    DECLARE_CONSTRUCTOR(MenuButton, Label)

    DECLARE_PROPERTY(ButtonFunction, function, Function)
    DECLARE_PROPERTY_D(int, state, State, NormalState)

    DECLARE_PROPERTY(Style, normalStyle, NormalStyle)
    DECLARE_PROPERTY(Style, pressedStyle, PressedStyle)
    DECLARE_PROPERTY(Style, highlightStyle, HighlightStyle)

    void paintComponent(QPainter *painter, const QRectF &sceneRect) override;
};

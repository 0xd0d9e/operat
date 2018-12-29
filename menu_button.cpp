#include "menu_button.h"

#include "debug.h"

void MenuButton::paintComponent(QPainter* painter, const QRectF& sceneRect)
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

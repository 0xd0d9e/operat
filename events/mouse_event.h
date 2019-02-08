#pragma once

#include "input_event.h"

#include <QPointF>

class QMouseEvent;

class MouseEvent : public InputEvent
{
public:
    MouseEvent(QMouseEvent* event, const QPointF& scenePos);

    QPointF getViewportPos() const;
    QPointF getScenePos() const;
    int getButton() const;
    int getButtons() const;
    int getModifiers() const;

private:
    QPointF viewportPos;
    QPointF scenePos;
    int button;
    int buttons;
    int modifiers;
};

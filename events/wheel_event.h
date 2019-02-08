#pragma once

#include "input_event.h"

#include <QPointF>

class QWheelEvent;

class WheelEvent : public InputEvent
{
public:
    WheelEvent(QWheelEvent* event, const QPointF& scenePos);

    int getDelta() const;
    QPointF getScenePos() const;

private:
    int delta;
    QPointF scenePos;
};


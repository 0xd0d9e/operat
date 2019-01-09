#pragma once

#include "event.h"

#include <QPointF>

class QWheelEvent;

class WheelEvent : public Event
{
public:
    WheelEvent(QWheelEvent* event, const QPointF& scenePos);

    int getDelta() const;
    QPointF getScenePos() const;

private:
    int delta;
    QPointF scenePos;
};


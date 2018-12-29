#pragma once

#include <QPointF>

class QMouseEvent;

class ViewportMouseEvent
{
public:
    ViewportMouseEvent(QMouseEvent* event, const QPointF& scenePos);

    QPointF getViewportPos() const;
    QPointF getScenePos() const;
    int getButton() const;
    int getButtons() const;
    int getModifiers() const;

private:
    QPointF scenePos;
    QMouseEvent* event;
};

#pragma once

#include "viewport_listener.h"
#include "component.h"

#include <QRectF>
#include <QSet>

class Viewport;
class Shape;

class ViewportControl : public ViewportListener, public Component
{
public:
    ViewportControl(Viewport* viewport);
    ~ViewportControl();

private:
    void mousePress(const ViewportMouseEvent& event) final;
    void mouseMove(const ViewportMouseEvent& event) final;
    void mouseRelease(const ViewportMouseEvent& event) final;

    void keyPress(const int key, const int modifiers) final;
    void keyRelease(const int key, const int modifiers) final;

    void wheel(const QPointF& scenePos, const int delta) final;

    void update(const double time) final;

    Viewport* viewport = nullptr;
    QPointF pressPos;
    QRectF pressRect;
    Shape* moveRect = nullptr;
    QSet<int> keys;
    double speed = 50.0;
    int zoomDuration = 100;
    int viewDuration = 1000;
};

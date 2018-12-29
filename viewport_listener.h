#pragma once

#include <QPointF>

class ViewportMouseEvent;

class ViewportListener
{
public:
    ViewportListener() = default;
    virtual ~ViewportListener() = default;

    virtual void mousePress(const ViewportMouseEvent& event);
    virtual void mouseMove(const ViewportMouseEvent& event);
    virtual void mouseRelease(const ViewportMouseEvent& event);

    virtual void keyPress(const int key, const int modifiers);
    virtual void keyRelease(const int key, const int modifiers);

    virtual void wheel(const QPointF& scenePos, const int delta);
};

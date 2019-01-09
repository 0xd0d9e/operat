#pragma once

#include "component.h"
#include "events/event_listener.h"

#include <QObject>
#include <QRectF>
#include <QSet>

class Camera;
class KeyEvent;
class MouseEvent;
class Shape;
class WheelEvent;

class CameraControl
        : public QObject
        , public Component
        , public EventListener
{
    Q_OBJECT
    Q_PROPERTY(QRectF viewRect READ getViewRect WRITE setViewRect)
public:
    void setCamera(Camera* camera);

    QRectF getViewRect() const;

public slots:
    void zoom(const double factor, const QPointF& scenePos, const int duration = 0);
    void setViewRect(const QRectF& rect, const int duration = 0);
    void popLocation(const int duration = 0);
    void pushLocation();

private:
    DECLARE_PREPARE_EVENT(Component)

    void mousePress(MouseEvent* event);
    void mouseMove(MouseEvent* event);
    void mouseRelease(MouseEvent* event);

    void keyPress(KeyEvent* event);
    void keyRelease(KeyEvent* event);

    void wheel(WheelEvent* event);

    void update(const double time) final;

    Camera* camera = nullptr;
    QPointF pressPos;
    QRectF pressRect;
    Shape* moveRect = nullptr;
    QSet<int> keys;
    double speed = 100.0;
    int zoomDuration = 100;
    int viewDuration = 1000;

    QList<QRectF> history;
};

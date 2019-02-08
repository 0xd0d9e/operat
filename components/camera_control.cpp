#include "camera_control.h"

#include "common/debug.h"
#include "common/utils.h"
#include "components/camera.h"
#include "components/updater.h"
#include "components/shape.h"
#include "events/key_event.h"
#include "events/mouse_event.h"
#include "events/wheel_event.h"

#include <QPropertyAnimation>

#include <cmath>

void CameraControl::setCamera(Camera* newCamera)
{
    camera = newCamera;
}

QRectF CameraControl::getViewRect() const
{
    return camera ? camera->getViewRect()
                  : QRectF();
}

void CameraControl::zoom(const double factor, const QPointF& scenePos, const int duration)
{
    if (!camera)
        return;

    QTransform transform;
    transform.translate(scenePos.x(), scenePos.y());
    transform.scale(factor, factor);
    transform.translate(-scenePos.x(), -scenePos.y());
    setViewRect(transform.mapRect(getViewRect()), duration);
}

void CameraControl::setViewRect(const QRectF& rect, const int duration)
{
    if (!camera)
        return;

    if (duration <= 0)
    {
        camera->setViewRect(rect);
        return;
    }

    const QRectF viewRect = camera->getViewRect();
    QPropertyAnimation* animation = new QPropertyAnimation(this, "viewRect");
    animation->setDuration(duration);
    animation->setStartValue(viewRect);
    if (qFuzzyCompare(viewRect.width(), rect.width()) && qFuzzyCompare(viewRect.height(), rect.height()))
    {
        const QPointF diff = rect.center() - viewRect.center();
        const double distance = hypot(diff.x(), diff.y());
        const QPointF center = (rect.center() + viewRect.center())/2.0;
        const double minDistance = std::max(viewRect.width(), viewRect.height());
        const double factor = std::min(6.0, std::max(distance / minDistance, 1.0));

        animation->setKeyValueAt(0.5, makeRect(center, rect.width() * factor, rect.height() * factor));
    }
    animation->setEndValue(rect);
    animation->setEasingCurve(QEasingCurve::InOutQuad);
    animation->start();
}

void CameraControl::popLocation(const int duration)
{
    if (history.empty())
        return;

    setViewRect(history.takeFirst(), duration);
}

void CameraControl::pushLocation()
{
    history.push_front(getViewRect());
}

void CameraControl::mousePress(MouseEvent* event)
{
    if (!camera)
        return;

    if (event->getButtons() == Qt::LeftButton && event->getModifiers() == Qt::ControlModifier)
    {
        Component* scene = camera->getScene();
        if (scene)
        {
            moveRect = scene->create<Shape>("moveRect",
            {
                {"style", Style(QPen(Qt::green, 2), QBrush(QColor("#aa00aa00")))},
                {"rect", QRectF()},
                {"type", Shape::Rectangle}
            });
        }
        pressPos = event->getScenePos();
    }
    else if (event->getButtons() == Qt::RightButton)
    {
        pressPos = event->getViewportPos();
        pressRect = camera->getViewRect();
    }
    else if (event->getButtons() == Qt::MiddleButton)
    {
        const QRectF viewRect = camera->getViewRect();
        const QRectF targetRect = makeRect(viewRect.center(), camera->getFrameSize());
        setViewRect(targetRect, viewDuration);
    }
}

void CameraControl::mouseMove(MouseEvent* event)
{
    if (!camera)
        return;

    if (event->getButtons() == Qt::LeftButton && event->getModifiers() == Qt::ControlModifier)
    {
        if (moveRect)
            moveRect->setRect({pressPos, event->getScenePos()});
    }
    else if (event->getButtons() == Qt::RightButton)
    {
        const QPointF scale = camera->getScale();
        const QPointF diff = pressPos - event->getViewportPos();
        QTransform transform;
        transform.translate(diff.x() / scale.x(), diff.y() / scale.y());
        camera->setViewRect(transform.mapRect(pressRect));
    }
}

void CameraControl::mouseRelease(MouseEvent* event)
{
    if (!camera)
        return;

    Q_UNUSED(event);
    if (event->getButton() == Qt::LeftButton && event->getModifiers() == Qt::ControlModifier)
    {
        if (moveRect)
        {
            QRectF rect = moveRect->getRect();
            if (std::max(rect.width(), rect.height()) < 10)
            {
                rect = camera->getViewRect();
                rect = makeRect(pressPos, rect.width(), rect.height());
            }
            pushLocation();
            setViewRect(rect, viewDuration);
            moveRect->deleteLater();
            moveRect = nullptr;
        }
    }
    else if (event->getButton() == Qt::RightButton)
    {
        if (pressPos == event->getViewportPos())
        {
            popLocation(viewDuration);
        }
    }
}

void CameraControl::keyPress(KeyEvent* event)
{
    if (!camera)
        return;

    const int key = event->getKey();
    keys.insert(key);

    QRectF rect;
    if (key == Qt::Key_1)
    {
        rect = QRectF(200, 150, 600, 600);
    }
    if (key == Qt::Key_2)
    {
        rect = QRectF(500, 450, 600, 600);
    }
    if (key == Qt::Key_3)
    {
        rect = QRectF(900, 600, 400, 400);
    }
    if (key == Qt::Key_4)
    {
        rect = QRectF(1200, 500, 350, 350);
    }

    if (!rect.isNull())
        setViewRect(rect, viewDuration);
}

void CameraControl::keyRelease(KeyEvent* event)
{
    keys.remove(event->getKey());
}

void CameraControl::wheel(WheelEvent* event)
{
    if (!camera)
        return;

    const double factor = event->getDelta() > 0 ? 0.8 : 1.2;
    zoom(factor, event->getScenePos(), zoomDuration);
}

void CameraControl::update(const double time)
{
    if (!camera)
        return;

    QPointF vec;
    if (keys.contains(Qt::Key_W))
        vec.setY(-1);
    else if (keys.contains(Qt::Key_S))
        vec.setY(1);
    if (keys.contains(Qt::Key_A))
        vec.setX(-1);
    else if (keys.contains(Qt::Key_D))
        vec.setX(1);

    if (!vec.isNull())
    {
        const QPointF scale = camera->getScale();
        const QPointF offset(vec.x() * speed / scale.x() * time,
                             vec.y() * speed / scale.y() * time);
        camera->moveBy(offset);
    }
}

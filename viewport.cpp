#include "viewport.h"

#include "common/config.h"
#include "common/debug.h"
#include "common/utils.h"
#include "components/camera.h"
#include "components/label.h"
#include "events/key_event.h"
#include "events/mouse_event.h"
#include "events/wheel_event.h"

#include <QPaintEvent>
#include <QPropertyAnimation>

#include <cmath>

Viewport::Viewport(QWidget* parent) : QWidget(parent)
{
    connect(&timer, &QTimer::timeout, this, &Viewport::update);

    timer.start(Config::paintInterval);

    setMouseTracking(true);
}

Component* Viewport::getScene() const
{
    return camera ? camera->getScene()
                  : nullptr;
}

Camera* Viewport::getCamera() const
{
    return camera;
}

void Viewport::setCamera(Camera* newCamera)
{
    if (camera == newCamera)
        return;

    camera = newCamera;
    if (camera)
        camera->setFrameSize(size());
    update();
}

void Viewport::paintEvent(QPaintEvent* event)
{
    if (!camera)
        return;

    QPainter painter(this);
    camera->paint(&painter, event->rect());
}

void Viewport::resizeEvent(QResizeEvent* event)
{
    QWidget::resizeEvent(event);

    if (!camera)
        return;

    camera->setFrameSize(event->size());
}

QPointF Viewport::sceneToViewport(const QPointF& scenePos) const
{
    return camera ? camera->sceneToViewport(scenePos)
                  : scenePos;
}

QPointF Viewport::viewportToScene(const QPointF& viewportPos) const
{
    return camera ? camera->viewportToScene(viewportPos)
                  : viewportPos;
}

QRectF Viewport::getViewRect() const
{
    return camera ? camera->getViewRect()
                  : QRectF();
}

void Viewport::setViewRect(const QRectF& rect)
{
    if (!camera)
        return;

    camera->setViewRect(rect);
    update();
}

void Viewport::moveBy(const QPointF& diff)
{
    if (!camera)
        return;

    QRectF viewRect = camera->getViewRect();
    viewRect.moveTopLeft(viewRect.topLeft() + diff);
    setViewRect(viewRect);
}

void Viewport::zoom(const double factor, const QPointF& scenePos)
{
    if (!camera)
        return;

    const QPointF pos = scenePos;

    QTransform transform;
    transform.translate(pos.x(), pos.y());
    transform.scale(factor, factor);
    transform.translate(-pos.x(), -pos.y());
    setViewRect(transform.mapRect(camera->getViewRect()));
}

void Viewport::zoomAnimated(const double factor, const QPointF& scenePos, const int duration)
{
    if (!camera)
        return;

    const QPointF pos = scenePos;

    QTransform transform;
    transform.translate(pos.x(), pos.y());
    transform.scale(factor, factor);
    transform.translate(-pos.x(), -pos.y());
    setViewRectAnimated(transform.mapRect(camera->getViewRect()), duration);
}

void Viewport::setViewRectAnimated(const QRectF& rect, const int duration)
{
    if (duration <= 0)
        setViewRect(rect);

    QRectF viewRect = camera->getViewRect();
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

double Viewport::getScale() const
{
    return camera ? camera->getScale()
                  : 1.0;
}

void Viewport::update()
{
    QWidget::update();
}

void Viewport::popLocation(const int duration)
{
    if (history.empty())
        return;

    if (duration > 0)
        setViewRectAnimated(history.takeFirst(), duration);
    else
        setViewRect(history.takeFirst());
}

void Viewport::pushLocation()
{
    history.push_front(getViewRect());
}

void Viewport::mousePressEvent(QMouseEvent* event)
{
    Component* scene = getScene();
    if (!scene)
        return;
    scene->postEvent(new MouseEvent(event, viewportToScene(event->pos())));
}

void Viewport::mouseMoveEvent(QMouseEvent* event)
{
    Component* scene = getScene();
    if (!scene)
        return;
    scene->postEvent(new MouseEvent(event, viewportToScene(event->pos())));
}

void Viewport::mouseReleaseEvent(QMouseEvent* event)
{
    Component* scene = getScene();
    if (!scene)
        return;
    scene->postEvent(new MouseEvent(event, viewportToScene(event->pos())));
}

void Viewport::keyPressEvent(QKeyEvent* event)
{
    Component* scene = getScene();
    if (!scene)
        return;
    scene->postEvent(new KeyEvent(event));
}

void Viewport::keyReleaseEvent(QKeyEvent* event)
{
    Component* scene = getScene();
    if (!scene)
        return;
    scene->postEvent(new KeyEvent(event));
}

void Viewport::wheelEvent(QWheelEvent* event)
{
    Component* scene = getScene();
    if (!scene)
        return;
    scene->postEvent(new WheelEvent(event, viewportToScene(event->pos())));
}

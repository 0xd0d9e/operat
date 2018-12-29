#include "viewport.h"

#include "config.h"
#include "debug.h"
#include "label.h"
#include "scene.h"
#include "utils.h"
#include "viewport_listener.h"
#include "viewport_mouse_event.h"

#include <QPaintEvent>
#include <QPropertyAnimation>

void viewportTest()
{
    Viewport viewport;
    viewport.resize(100, 100);
    viewport.setViewRect({10, 10, 100, 100});

    const QPointF expectedViewportPos(0, 0);
    const QPointF viewportPos = viewport.sceneToViewport({10, 10});
    const QPointF expectedScenePos(20, 20);
    const QPointF scenePos = viewport.viewportToScene({10, 10});

    TEST_ASSERT(viewportPos, expectedViewportPos);
    TEST_ASSERT(scenePos, expectedScenePos);
}


Viewport::Viewport(QWidget* parent) : QWidget(parent)
    , overlay(new Component(nullptr, "overlay"))
{
    TEST(viewportTest);
    connect(&timer, &QTimer::timeout, this, &Viewport::update);

    //timer.start(Config::paintInterval);

    setMouseTracking(true);

    overlay->create<Label>("debugLabel");
}

Component* Viewport::getOverlay() const
{
    return overlay;
}

void Viewport::addListener(ViewportListener* listener)
{
    listeners.push_back(listener);
}

void Viewport::removeListener(ViewportListener* listener)
{
    listeners.remove(listener);
}

Scene* Viewport::getScene() const
{
    return scene;
}

void Viewport::setScene(Scene* scene)
{
    this->scene = scene;
}

void Viewport::paintEvent(QPaintEvent* event)
{
    Q_UNUSED(event);

    updateBuffer();

    QPainter painter(this);
    painter.drawPixmap(0, 0, frameBuffer);
}

void Viewport::resizeEvent(QResizeEvent* event)
{
    QWidget::resizeEvent(event);
    if (viewRect.isNull())
        viewRect = QRectF(0, 0, width(), height());
    frameBuffer = QPixmap(width(), height());
    updateViewRect();
}

const QTransform& Viewport::getTransform() const
{
    return transform;
}

const QTransform&Viewport::getInverseTransform() const
{
    return inverseTransform;
}

QRectF Viewport::getViewRect() const
{
    return viewRect;
}

void Viewport::setViewRect(const QRectF& rect)
{
    viewRect = rect;
    updateViewRect();
}

void Viewport::moveBy(const QPointF& diff)
{
    viewRect.moveTopLeft(viewRect.topLeft() + diff);
    updateViewRect();
}

void Viewport::zoom(const double factor, const QPointF& scenePos)
{
    const QPointF pos = scenePos;

    QTransform transform;
    transform.translate(pos.x(), pos.y());
    transform.scale(factor, factor);
    transform.translate(-pos.x(), -pos.y());
    setViewRect(transform.mapRect(viewRect));
}

void Viewport::zoomAnimated(const double factor, const QPointF& scenePos, const int duration)
{
    const QPointF pos = scenePos;

    QTransform transform;
    transform.translate(pos.x(), pos.y());
    transform.scale(factor, factor);
    transform.translate(-pos.x(), -pos.y());
    setViewRectAnimated(transform.mapRect(viewRect), duration);
}

void Viewport::setViewRectAnimated(const QRectF& rect, const int duration)
{
    if (duration <= 0)
        setViewRect(rect);
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

QPointF Viewport::sceneToViewport(const QPointF& scenePos) const
{
    return transform.map(scenePos);
}

QPointF Viewport::viewportToScene(const QPointF& viewportPos) const
{
    return inverseTransform.map(viewportPos);
}

double Viewport::getScale() const
{
    return std::max(width() / viewRect.width(), height() / viewRect.height());
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
    history.push_front(viewRect);
}

void Viewport::updateBuffer()
{
    frameBuffer.fill();

    if (!scene && !overlay)
        return;

    QPainter painter(&frameBuffer);

    if (overlay)
        overlay->paint(&painter, {0.0, 0.0, (double) width(), (double) height()});

    if (scene)
    {
        const QRectF sceneRect = inverseTransform.mapRect(QRectF(0, 0, width(), height()));
        painter.setTransform(transform);
        scene->paint(&painter, sceneRect);
    }

    QStringList lines;
    lines << QString("Scale %1x%2").arg(viewRect.width() / width()).arg(viewRect.height() / height());
    lines << QString("Center x:%1, y:%2")
             .arg(viewRect.center().x())
             .arg(viewRect.center().y());
    overlay->get<Label>("debugLabel")->setText(lines);
}

void Viewport::updateViewRect()
{
    const double scale = getScale();

    transform = QTransform();
    transform.scale(scale, scale);
    transform.translate(-viewRect.x(), -viewRect.y());

    inverseTransform = QTransform();
    inverseTransform.translate(viewRect.x(), viewRect.y());
    inverseTransform.scale(1.0/scale, 1.0/scale);
    update();
}

void Viewport::mousePressEvent(QMouseEvent* event)
{
    if (listeners.empty())
        return;

    const ViewportMouseEvent viewportMouseEvent(event, viewportToScene(event->pos()));

    for (ViewportListener* listener : listeners)
        listener->mousePress(viewportMouseEvent);
}

void Viewport::mouseMoveEvent(QMouseEvent* event)
{
    if (listeners.empty())
        return;

    const ViewportMouseEvent viewportMouseEvent(event, viewportToScene(event->pos()));

    for (ViewportListener* listener : listeners)
        listener->mouseMove(viewportMouseEvent);
}

void Viewport::mouseReleaseEvent(QMouseEvent* event)
{
    if (listeners.empty())
        return;

    const ViewportMouseEvent viewportMouseEvent(event, viewportToScene(event->pos()));

    for (ViewportListener* listener : listeners)
        listener->mouseRelease(viewportMouseEvent);
}

void Viewport::keyPressEvent(QKeyEvent* event)
{
    if (listeners.empty())
        return;

    for (ViewportListener* listener : listeners)
        listener->keyPress(event->key(), event->modifiers());
}

void Viewport::keyReleaseEvent(QKeyEvent* event)
{
    if (listeners.empty())
        return;

    for (ViewportListener* listener : listeners)
        listener->keyRelease(event->key(), event->modifiers());
}

void Viewport::wheelEvent(QWheelEvent* event)
{
    if (listeners.empty())
        return;

    const QPointF scenePos = viewportToScene(event->pos());
    for (ViewportListener* listener : listeners)
        listener->wheel(scenePos, event->delta());
}

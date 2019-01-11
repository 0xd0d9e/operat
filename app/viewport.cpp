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
    timeMeter.start();

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
    camera->render(&painter, event->rect());
    ++frameCount;

    if (showFps)
    {
        const double fps = frameCount / (timeMeter.elapsed() / 1000.0);
        //painter.setCompositionMode(QPainter::RasterOp_SourceXorDestination);
        painter.setPen(QPen(QColor(Qt::red), 0));
        painter.setFont(QFont("Arial", 16, QFont::Bold));
        painter.drawText(10, 10 + painter.fontMetrics().lineSpacing(),
                         QString("FPS: %1").arg(fps, 0, 'g', 2));
    }
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

void Viewport::update()
{
    QWidget::update();
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

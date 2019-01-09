#include "camera.h"

void Camera::paint(QPainter* painter, const QRectF& sceneRect)
{
    if (rendering)
        return;
    Q_UNUSED(sceneRect);

    updateTransform();
    updateFrameBuffer();
    painter->drawPixmap(0, 0, frameBuffer);
}

const QTransform& Camera::getTransform() const
{
    return transform;
}

const QTransform& Camera::getInverseTransform() const
{
    return inverseTransform;
}

QPointF Camera::sceneToViewport(const QPointF& scenePos) const
{
    return transform.map(scenePos);
}

QPointF Camera::viewportToScene(const QPointF& viewportPos) const
{
    return inverseTransform.map(viewportPos);
}

double Camera::getScale() const
{
    const QRectF viewRect = getViewRect();
    const QSizeF frameSize = getFrameSize();
    return std::min(frameSize.width() / viewRect.width(), frameSize.height() / viewRect.height());
}

Component* Camera::getScene() const
{
    return scene;
}

void Camera::setScene(Component* newScene)
{
    scene = newScene;
}

Component* Camera::getOverlay() const
{
    return overlay;
}

void Camera::setOverlay(Component* newOverlay)
{
    overlay = newOverlay;
}


void Camera::moveBy(const QPointF& diff)
{
    QRectF viewRect = getViewRect();
    viewRect.moveTopLeft(viewRect.topLeft() + diff);
    setViewRect(viewRect);
}

void Camera::zoom(const double factor, const QPointF& scenePos)
{
    QTransform transform;
    transform.translate(scenePos.x(), scenePos.y());
    transform.scale(factor, factor);
    transform.translate(-scenePos.x(), -scenePos.y());
    setViewRect(transform.mapRect(getViewRect()));
}

void Camera::updateTransform()
{
    const QRectF viewRect = getViewRect();
    const QSizeF frameSize = getFrameSize();
    const double scale = getScale();

    transform = QTransform();
    transform.translate(frameSize.width() / 2.0, frameSize.height() / 2.0);
    transform.scale(scale, scale);
    transform.translate(-viewRect.width() / 2.0, -viewRect.height() / 2.0);
    transform.translate(-viewRect.x(), -viewRect.y());

    inverseTransform = QTransform();
    inverseTransform.translate(viewRect.x(), viewRect.y());
    inverseTransform.translate(viewRect.width() / 2.0, viewRect.height() / 2.0);
    inverseTransform.scale(1.0/scale, 1.0/scale);
    inverseTransform.translate(-frameSize.width() / 2.0, -frameSize.height() / 2.0);
}

void Camera::updateFrameBuffer()
{
    rendering = true;
    const QSizeF frameSize = getFrameSize();
    frameBuffer = QPixmap(frameSize.width(), frameSize.height());
    frameBuffer.fill();

    if (!scene || frameSize.isNull())
        return;

    const QRectF sceneRect = inverseTransform.mapRect(QRectF(0, 0, frameSize.width(), frameSize.height()));

    QPainter painter(&frameBuffer);
    painter.save();
    painter.setTransform(transform);
    scene->paint(&painter, sceneRect);
    painter.restore();
    rendering = false;
}

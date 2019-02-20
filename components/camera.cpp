#include "camera.h"

#include "common/debug.h"

void Camera::render(QPainter* painter, const QRectF& sceneRect)
{
//    DEBUG_LOCATION();
//    DEBUG_VALUE(getName());
//    DEBUG_VALUE(sceneRect);

    if (rendering)
        return;

    if (focused)
    {
        QRectF viewRect = getViewRect();
        viewRect.moveCenter(focused->getPos());
        setViewRect(viewRect);
    }

    const QSizeF frameSize = getFrameSize();

    if (frameSize.isNull())
        return;

    if (getViewRect().isNull())
        return;

    updateTransform();
    updateFrameBuffer(sceneRect.isNull() ? QRectF(0, 0, frameSize.width(), frameSize.height()) : sceneRect);
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

QPointF Camera::getScale() const
{
    const QRectF viewRect = getViewRect();
    const QSizeF frameSize = getFrameSize();
    double scaleX = frameSize.width() / viewRect.width();
    double scaleY = frameSize.height() / viewRect.height();

    if (getKeepAspect())
    {
        scaleX = scaleY = std::min(scaleX, scaleY);
    }
    return QPointF(scaleX, scaleY);
}

void Camera::init()
{
    Component::init();
    if (properties.contains(frameSizeKey()))
        onFrameSizeChanged(getFrameSize());
}

void Camera::updateTransform()
{
    const QRectF viewRect = getViewRect();
    const QSizeF frameSize = getFrameSize();
    const QPointF scale = getScale();

    transform = QTransform();
    transform.translate(frameSize.width() / 2.0, frameSize.height() / 2.0);
    transform.scale(scale.x(), scale.y());
    transform.translate(-viewRect.width() / 2.0, -viewRect.height() / 2.0);
    transform.translate(-viewRect.x(), -viewRect.y());

    inverseTransform = QTransform();
    inverseTransform.translate(viewRect.x(), viewRect.y());
    inverseTransform.translate(viewRect.width() / 2.0, viewRect.height() / 2.0);
    inverseTransform.scale(1.0/scale.x(), 1.0/scale.y());
    inverseTransform.translate(-frameSize.width() / 2.0, -frameSize.height() / 2.0);
}

void Camera::updateFrameBuffer(const QRectF& rect)
{
    rendering = true;

    if (frameBuffer.isNull() || !(scene || overlay) || rect.isNull())
    {
        return;
    }

    QPainter painter(&frameBuffer);
    painter.setPen(Qt::NoPen);
    painter.setBrush(QBrush(getClearColor()));
    painter.drawRect(rect);

    if (scene)
    {
        painter.save();
        painter.setTransform(transform);
        scene->paint(&painter, inverseTransform.mapRect(rect));
        painter.restore();
    }

    if (overlay)
    {
        overlay->paint(&painter, rect);
    }

    rendering = false;
}

void Camera::onFrameSizeChanged(const QSizeF& size)
{
    frameBuffer = QPixmap(size.width(), size.height());
    frameBuffer.fill();
}

Component* Camera::getFocused() const
{
    return focused;
}

void Camera::setFocused(Component* value)
{
    focused = value;
}

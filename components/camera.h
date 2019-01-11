#pragma once

#include "component.h"

class Camera : public Component
{
public:
    DECLARE_CONSTRUCTOR(Camera, Component)

    DECLARE_PROPERTY_C(QSizeF, frameSize, FrameSize, onFrameSizeChanged)
    DECLARE_PROPERTY(QRectF, viewRect, ViewRect)
    DECLARE_PROPERTY_D(QColor, clearColor, ClearColor, QColor(Qt::white))
    DECLARE_PROPERTY_D(bool, keepAspect, KeepAspect, true)

    void render(QPainter *painter, const QRectF &sceneRect);

    const QTransform& getTransform() const;
    const QTransform& getInverseTransform() const;

    QPointF sceneToViewport(const QPointF& scenePos) const;
    QPointF viewportToScene(const QPointF& viewportPos) const;

    Component* getScene() const;
    void setScene(Component* scene);

    Component* getOverlay() const;
    void setOverlay(Component* overlay);

    void moveBy(const QPointF& diff);
    void zoom(const double factor, const QPointF& scenePos);

    QPointF getScale() const;
private:
    void init() final;
    void updateTransform();
    void updateFrameBuffer(const QRectF& rect);
    void onFrameSizeChanged(const QSizeF& size);

    QPixmap frameBuffer;
    QTransform transform;
    QTransform inverseTransform;
    Component* scene = nullptr;
    Component* overlay = nullptr;
    bool rendering = false;
};

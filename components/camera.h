#pragma once

#include "component.h"

class Camera : public Component
{
public:
    DECLARE_CONSTRUCTOR(Camera, Component)

    DECLARE_PROPERTY(QSizeF, frameSize, FrameSize)
    DECLARE_PROPERTY(QRectF, viewRect, ViewRect)

    void paint(QPainter *painter, const QRectF &sceneRect) final;

    const QTransform& getTransform() const;
    const QTransform& getInverseTransform() const;

    QPointF sceneToViewport(const QPointF& scenePos) const;
    QPointF viewportToScene(const QPointF& viewportPos) const;
    double getScale() const;

    Component* getScene() const;
    void setScene(Component* scene);

    Component* getOverlay() const;
    void setOverlay(Component* overlay);

    void moveBy(const QPointF& diff);
    void zoom(const double factor, const QPointF& scenePos);

private:
    void updateTransform();
    void updateFrameBuffer();

    QPixmap frameBuffer;
    QTransform transform;
    QTransform inverseTransform;
    Component* scene = nullptr;
    Component* overlay = nullptr;
    bool rendering = false;
};

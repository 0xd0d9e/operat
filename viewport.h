#pragma once

#include <QTimer>
#include <QWidget>

class Scene;
class ViewportListener;
class Component;

class Viewport : public QWidget
{
    Q_OBJECT
    Q_PROPERTY(QRectF viewRect READ getViewRect WRITE setViewRect)
public:
    Viewport(QWidget* parent = 0);

    Component* getOverlay() const;

    void addListener(ViewportListener* listener);
    void removeListener(ViewportListener* listener);

    Scene* getScene() const;
    void setScene(Scene* scene);

    void paintEvent(QPaintEvent* event);
    void resizeEvent(QResizeEvent *event);

    const QTransform& getTransform() const;
    const QTransform& getInverseTransform() const;

    QRectF getViewRect() const;
    void setViewRect(const QRectF& rect);
    void moveBy(const QPointF& diff);
    void zoom(const double factor, const QPointF& scenePos);
    void zoomAnimated(const double factor, const QPointF& scenePos, const int duration);
    void setViewRectAnimated(const QRectF& rect, const int duration);

    QPointF sceneToViewport(const QPointF& scenePos) const;
    QPointF viewportToScene(const QPointF& viewportPos) const;

    double getScale() const;

public slots:
    void update();

    void popLocation(const int duration = 0);
    void pushLocation();

private:
    void updateBuffer();
    void updateViewRect();
    void mousePressEvent(QMouseEvent* event) final;
    void mouseMoveEvent(QMouseEvent* event) final;
    void mouseReleaseEvent(QMouseEvent* event) final;
    void keyPressEvent(QKeyEvent* event) final;
    void keyReleaseEvent(QKeyEvent* event) final;
    void wheelEvent(QWheelEvent* event) final;

    Component* overlay = nullptr;
    Scene* scene = nullptr;
    QRectF viewRect;
    QTransform transform;
    QTransform inverseTransform;
    std::list<ViewportListener*> listeners;
    QTimer timer;
    QPixmap frameBuffer;
    QList<QRectF> history;
};

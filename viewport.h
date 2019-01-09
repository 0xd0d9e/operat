#pragma once

#include <QTimer>
#include <QWidget>

class Camera;
class Component;

class Viewport : public QWidget
{
    Q_OBJECT
    Q_PROPERTY(QRectF viewRect READ getViewRect WRITE setViewRect)
public:
    Viewport(QWidget* parent = 0);

    Camera* getCamera() const;
    void setCamera(Camera* camera);

    Component* getScene() const;

    void paintEvent(QPaintEvent* event);
    void resizeEvent(QResizeEvent *event);

    QPointF sceneToViewport(const QPointF& scenePos) const;
    QPointF viewportToScene(const QPointF& viewportPos) const;

    QRectF getViewRect() const;
    void setViewRect(const QRectF& rect);
    void moveBy(const QPointF& diff);
    void zoom(const double factor, const QPointF& scenePos);
    void zoomAnimated(const double factor, const QPointF& scenePos, const int duration);
    void setViewRectAnimated(const QRectF& rect, const int duration);

    double getScale() const;
public slots:
    void update();

    void popLocation(const int duration = 0);
    void pushLocation();

private:
    void mousePressEvent(QMouseEvent* event) final;
    void mouseMoveEvent(QMouseEvent* event) final;
    void mouseReleaseEvent(QMouseEvent* event) final;
    void keyPressEvent(QKeyEvent* event) final;
    void keyReleaseEvent(QKeyEvent* event) final;
    void wheelEvent(QWheelEvent* event) final;

    QTimer timer;
    Camera* camera;
    QList<QRectF> history;
};

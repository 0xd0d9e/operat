#pragma once

#include <QElapsedTimer>
#include <QTimer>
#include <QWidget>

class Camera;
class Component;

class Viewport : public QWidget
{
    Q_OBJECT
public:
    Viewport(QWidget* parent = 0);

    Camera* getCamera() const;
    void setCamera(Camera* camera);

    Component* getScene() const;

    void paintEvent(QPaintEvent* event);
    void resizeEvent(QResizeEvent *event);

    QPointF sceneToViewport(const QPointF& scenePos) const;
    QPointF viewportToScene(const QPointF& viewportPos) const;

public slots:
    void update();

private:
    void mousePressEvent(QMouseEvent* event) final;
    void mouseMoveEvent(QMouseEvent* event) final;
    void mouseReleaseEvent(QMouseEvent* event) final;
    void keyPressEvent(QKeyEvent* event) final;
    void keyReleaseEvent(QKeyEvent* event) final;
    void wheelEvent(QWheelEvent* event) final;

    QTimer timer;
    Camera* camera;

    bool showFps = true;
    QElapsedTimer timeMeter;
    int frameCount = 0;
};

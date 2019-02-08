#pragma once

#include "app/stage.h"
#include "components/camera_control.h"
#include "components/updater.h"
#include "events/event_listener.h"

#include <QObject>

class Camera;

class PreviewStage
        : public QObject
        , public Stage
        , public Component
        , public EventListener
{
    Q_OBJECT
public:
    PreviewStage();

    void setViewport(Viewport* viewport) final;

signals:
    void escape();

private:
    DECLARE_PREPARE_EVENT(Component)

    void keyRelease(KeyEvent* event);

    Updater updater;
    Camera* camera;
    CameraControl cameraControl;
};


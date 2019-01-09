#pragma once

#include "components/scene.h"
#include "components/camera_control.h"
#include "events/event_listener.h"
#include "stage.h"

class Camera;

class PreviewStage
        : public Stage
        , public Component
        , public EventListener
{
public:
    PreviewStage(std::function<void ()> escapeFunction);

    void setViewport(Viewport* viewport) final;

private:
    DECLARE_PREPARE_EVENT(Component)

    void keyRelease(KeyEvent* event);

    Scene scene;
    Camera* camera;
    CameraControl cameraControl;
    std::function<void ()> escapeFunction;
};


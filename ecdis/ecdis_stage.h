#pragma once

#include "app/stage.h"
#include <components/scene_manager.h>

#include "route_monitor_scene.h"

class EcdisStage
        : public Stage
        , public Component
{
public:
    EcdisStage();

    void setViewport(Viewport* viewport) final;

private:
    SceneManager sceneManager;
    RouteMonitorScene routeMonitorScene;
};

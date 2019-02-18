#pragma once

#include "components/scene.h"

class CameraControl;


class RouteMonitorScene : public Scene
{
public:
    RouteMonitorScene();

    virtual Camera* getCamera() const;

private:
    CameraControl* cameraControl;
};

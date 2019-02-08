#pragma once

#include "app/stage.h"
#include "components/camera_control.h"
#include "components/scene.h"
#include "components/scene_manager.h"
#include "components/updater.h"
#include "events/event_listener.h"

#include <QObject>

class Camera;

class GridsLogic
{
public:
    virtual void start() = 0;
    virtual void exit() = 0;
};

class Char : public Component
{
public:
    DECLARE_CONSTRUCTOR(Char, Component)

    void init();
};

class GridsScene : public Scene
{
public:
    GridsScene(GridsLogic* grids);

    virtual Camera* getCamera() const;

private:
    GridsLogic* grids;
    CameraControl* cameraControl;
};

class GridsMenuScene : public Scene
{
public:
    GridsMenuScene(GridsLogic* grids);

    virtual Camera* getCamera() const;

private:
    GridsLogic* grids;
};


class GridsStage
        : public Stage
        , public Component
        , public GridsLogic
{
public:
    GridsStage();

    void setViewport(Viewport* viewport) final;

private:
    void start();
    void exit();

    SceneManager sceneManager;
    GridsScene mainScene;
    GridsMenuScene menuScene;
};


#include "scene_manager.h"

#include "app/viewport.h"
#include "common/debug.h"
#include "camera.h"
#include "updater.h"
#include "scene.h"

SceneManager::SceneManager()
    : updater(new Updater())
{
}

SceneManager::~SceneManager()
{
    delete updater;
}

void SceneManager::setViewport(Viewport* newViewport)
{
    if (viewport == newViewport)
        return;

    if (viewport)
        viewport->setCamera(nullptr);

    viewport = newViewport;

    if (viewport && scene)
        viewport->setCamera(scene->getCamera());
    else
        updater->setEnabled(false);
}

void SceneManager::setScene(Scene* newScene)
{
    if (scene == newScene)
        return;

    updater->setEnabled(false);

    if (scene)
    {
        scene->getCamera()->setScene(nullptr);
        updater->removeChild(scene);
    }

    scene = newScene;

    if (scene)
    {
        updater->addChild(scene);
        if (viewport)
            viewport->setCamera(scene->getCamera());
        updater->setEnabled(true);
        scene->getCamera()->setScene(updater);
    }
    else
    {
        if (viewport)
            viewport->setCamera(nullptr);
    }
}

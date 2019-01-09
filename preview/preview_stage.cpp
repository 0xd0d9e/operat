#include "preview_stage.h"

#include "components/grid.h"
#include "components/persone.h"
#include "components/sprite.h"
#include "components/camera.h"
#include "events/key_event.h"
#include "viewport.h"

PreviewStage::PreviewStage(std::function<void ()> escapeFunction) : escapeFunction(escapeFunction)
{
    camera = scene.create<Camera>();
    camera->setScene(&scene);
    camera->setViewRect({0, 0, 800, 600});
    scene.addChild(this);
    scene.addChild(&cameraControl);
    scene.create<Sprite>("worldMap", {{"image", "WorldMap"}});
    scene.create<Grid>("grid", {{"size", 32}, {"pen", QPen(Qt::black)}});
    scene.create<Persone>("persone")->setScale(32);
    cameraControl.setCamera(camera);
}

void PreviewStage::setViewport(Viewport* viewport)
{
    if (viewport)
        viewport->setCamera(camera);

    scene.setEnabled(viewport != nullptr);
}

void PreviewStage::keyRelease(KeyEvent* event)
{
    if (event->getKey() == Qt::Key_Escape)
    {
        escapeFunction();
    }
}

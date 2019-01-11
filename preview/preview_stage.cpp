#include "preview_stage.h"

#include "app/viewport.h"
#include "components/camera.h"
#include "components/display.h"
#include "components/grid.h"
#include "components/persone.h"
#include "components/sprite.h"
#include "events/key_event.h"

PreviewStage::PreviewStage(std::function<void ()> escapeFunction) : escapeFunction(escapeFunction)
{
    camera = scene.create<Camera>("camera", {{"viewRect", QRectF(-400, -300, 800, 600)}});
    camera->setScene(&scene);

    const QSizeF mapSize(4072, 1765);

    scene.addChild(this);
    scene.addChild(&cameraControl);
    Sprite* map = scene.create<Sprite>("worldMap", {{"image", "WorldMap"},
                                                    {"pos", QPointF(-mapSize.width()/2, -mapSize.height()/2)}});
    scene.create<Grid>("grid", {{"size", 32}, {"pen", QPen(Qt::black)}});
    scene.create<Persone>("ship");

    Component* overlay = new Component();
    camera->setOverlay(overlay);

    const double aspect = mapSize.height() / mapSize.width();
    const double width = 600.0;
    Camera* mapCamera = overlay->create<Camera>("worldCamera", {{"frameSize", QSizeF(width, width * aspect)},
                                                                {"viewRect", QRectF(map->getPos(), mapSize)}});

    mapCamera->setScene(&scene);
    mapCamera->setKeepAspect(false);
    Display* display = overlay->create<Display>("mapDisplay", {{"pos", QPointF(10, 10)}});
    display->setCamera(mapCamera);

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

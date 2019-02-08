#include "preview_stage.h"

#include "app/viewport.h"
#include "components/camera.h"
#include "components/display.h"
#include "components/grid.h"
#include "components/persone.h"
#include "components/sprite.h"
#include "events/key_event.h"

PreviewStage::PreviewStage()
{
    camera = updater.create<Camera>("camera", {{"viewRect", QRectF(-400, -300, 800, 600)}});
    camera->setScene(&updater);

    const QSizeF mapSize(4072, 1765);

    updater.addChild(this);
    updater.addChild(&cameraControl);
    Sprite* map = updater.create<Sprite>("worldMap", {{"image", "WorldMap"},
                                                    {"pos", QPointF(-mapSize.width()/2, -mapSize.height()/2)}});
    updater.create<Grid>("grid", {{"size", 32}, {"pen", QPen(Qt::black)}});
    updater.create<Persone>("ship");

    Component* overlay = new Component();
    camera->setOverlay(overlay);

    const double aspect = mapSize.height() / mapSize.width();
    const double width = 600.0;
    Camera* mapCamera = overlay->create<Camera>("worldCamera", {{"frameSize", QSizeF(width, width * aspect)},
                                                                {"viewRect", QRectF(map->getPos(), mapSize)}});

    mapCamera->setScene(&updater);
    mapCamera->setKeepAspect(false);
    Display* display = overlay->create<Display>("mapDisplay", {{"pos", QPointF(10, 10)}});
    display->setCamera(mapCamera);

    cameraControl.setCamera(camera);
}

void PreviewStage::setViewport(Viewport* viewport)
{
    if (viewport)
        viewport->setCamera(camera);

    updater.setEnabled(viewport != nullptr);
}

void PreviewStage::keyRelease(KeyEvent* event)
{
    if (event->getKey() == Qt::Key_Escape)
    {
        emit escape();
    }
}

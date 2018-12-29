#include "preview_stage.h"

#include "grid.h"
#include "persone.h"
#include "sprite.h"
#include "viewport.h"

PreviewStage::PreviewStage()
{
    Component* root = scene.getRoot();

    root->addChild(&viewportControl);
    root->create<Sprite>("worldMap", {{"image", "WorldMap"}});
    root->create<Grid>("grid", {{"size", 32}, {"pen", QPen(Qt::black)}});
    root->create<Persone>("persone")->setScale(32);
}

void PreviewStage::setViewport(Viewport* viewport)
{
    viewport->setScene(&scene);
    viewportControl.setViewport(viewport);
}

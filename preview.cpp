#include "preview.h"

#include "debug.h"
#include "grid.h"
#include "persone.h"
#include "resource_manager.h"
#include "sprite.h"
#include "utils.h"
#include "resource_manager.h"

Preview::Preview()
    : viewportControl(&viewport)
{
    viewport.setScene(&scene);

    auto& resourceManager = ResourceManager::instance();
    resourceManager.addImage("WorldMap", QImage(":/assets/images/world_map.jpg"));
    resourceManager.setPreset("persone-hand", {{"type", Shape::Ellipse},
                                               {"pen", QPen(Qt::black, 0)},
                                               {"brush", QBrush("#ffaaaa")},
                                               {"rect", makeRect(0.25, 0.25)}});
    resourceManager.setPreset("persone-body", {{"type", Shape::Ellipse},
                                               {"pen", QPen(Qt::black, 0)},
                                               {"brush", QBrush("#229922")},
                                               {"rect", makeRect(0.8, 0.8)}});

    Component* root = scene.getRoot();

    root->addChild(&viewportControl);
    root->create<Sprite>("worldMap", {{"image", "WorldMap"}});
    root->create<Grid>("grid", {{"size", 32}, {"pen", QPen(Qt::black)}});
    root->create<Persone>("persone")->setScale(32);
    root->dump();
}

void Preview::start()
{
    viewport.show();
    viewport.resize(800, 600);
    viewport.setViewRect(makeRect(800, 600));
}

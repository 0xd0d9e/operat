#include "level.h"

#include "components/scene.h"
#include "components/persone.h"

Level::Level(const double tileSize)
    : tileSize(tileSize)
    , scene(new Scene())
{
}

Scene* Level::getScene() const
{
    return scene;
}

void Level::addPersone(Persone* persone)
{
    scene->getRoot()->addChild(persone);
}

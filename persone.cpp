#include "persone.h"

#include "event.h"
#include "shape.h"
#include "utils.h"

Persone::Persone(Component* parent, const QString& name, const QVariantMap& properties)
    : Component(parent, name, properties)
    , body(create<Shape>("body", {{"preset", "persone-body"}}))
    , lhand(create<Shape>("lhand", {{"preset", "persone-hand"}}))
    , rhand(create<Shape>("rhand", {{"preset", "persone-hand"}}))
{
    lhand->setPos({0.25, 0.25});
    rhand->setPos({0.25,-0.25});

    addEvent(new Event([this](){nextDir();}, Event::Regular, 1000, -5000));
}

void Persone::update(const double time)
{
    Component::update(time);
}

void Persone::onDirChanged(const int dir)
{
    switch (dir)
    {

    case Left:
        lhand->setPos({-0.25, 0.25});
        rhand->setPos({-0.25,-0.25});
        break;

    case Right:
        lhand->setPos({ 0.25, 0.25});
        rhand->setPos({ 0.25,-0.25});
        break;

    case Top:
        lhand->setPos({-0.25,-0.25});
        rhand->setPos({ 0.25,-0.25});
        break;

    case Down:
        lhand->setPos({ 0.25, 0.25});
        rhand->setPos({-0.25, 0.25});
        break;

    }
}

void Persone::nextDir()
{
    int dir = getDir();
    if (++dir > Down)
        dir = Left;
    setDir(dir);
}

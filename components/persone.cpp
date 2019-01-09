#include "persone.h"

#include "common/utils.h"
#include "events/event.h"
#include "events/invoke_event.h"
#include "shape.h"

#include <cmath>

Persone::Persone(Component* parent, const QString& name, const QVariantMap& properties)
    : Component(parent, name, properties)
    , body(create<Shape>("body", {{"preset", "persone-body"}}))
    , lhand(create<Shape>("lhand", {{"preset", "persone-hand"}}))
    , rhand(create<Shape>("rhand", {{"preset", "persone-hand"}}))
{
    lhand->setPos({0.25, 0.25});
    rhand->setPos({0.25,-0.25});

    postEvent(new InvokeEvent([this](){rotate();}, true, 0, -1000));
}

void Persone::update(const double time)
{
    Component::update(time);
}

void Persone::rotate()
{
    const double rotation = getRotation() + M_PI / (180.0*2);
    setRotation(rotation);
    const double speed = 30.0 / 50;
    setPos(getPos() + QPointF(cos(rotation), sin(rotation)) * speed);
}

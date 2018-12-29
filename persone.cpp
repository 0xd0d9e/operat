#include "persone.h"

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
}

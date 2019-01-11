#include "persone.h"
#include "sprite.h"

#include "common/utils.h"
#include "events/event.h"
#include "events/invoke_event.h"
#include "shape.h"

#include <cmath>

void Persone::update(const double time)
{
    Component::update(time);
}

void Persone::init()
{
    /*body = create<Shape>("body", {{"preset", "persone-body"}});
    lhand = create<Shape>("lhand", {{"preset", "persone-hand"}});
    rhand = create<Shape>("rhand", {{"preset", "persone-hand"}});

    lhand->setPos({0.25, 0.25});
    rhand->setPos({0.25,-0.25});*/
    create<Sprite>("ship", {{"image", "Ship"},
                            {"origin", QPointF(-0.5, -0.5)},
                            {"minScale", 0.25}});

    create<Shape>("marker", {{"type", Shape::Ellipse},
                             {"rect", QRectF(-10, -10, 20, 20)},
                             {"style", Style(QPen(Qt::red, 2), QBrush(Qt::red))},
                             {"maxScale", 0.25}});

    postEvent(new InvokeEvent([this](){rotate();}, true, 0, -1000));
}

void Persone::rotate()
{
    const double rotation = getRotation() + M_PI / (180.0*2);
    setRotation(rotation);
    const double speed = 30.0 / 50;
    setPos(getPos() + QPointF(cos(rotation), sin(rotation)) * speed);
}

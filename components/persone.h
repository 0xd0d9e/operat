#pragma once

#include "component.h"
#include "shape.h"

class Persone : public Component
{
public:
    DECLARE_CONSTRUCTOR(Persone, Component)

    DECLARE_PROPERTY(QString, group, Group)

    void update(const double time) override;

private:
    void init() override;
    void rotate();

    Shape* body;
    Shape* lhand;
    Shape* rhand;
};

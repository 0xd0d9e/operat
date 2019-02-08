#pragma once

#include "component.h"

class Camera;

class Scene : public Component
{
public:
    DECLARE_CONSTRUCTOR(Scene, Component)

    virtual Camera* getCamera() const = 0;

};

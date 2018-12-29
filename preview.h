#pragma once

#include "scene.h"
#include "viewport.h"
#include "viewport_control.h"

class Preview
{
public:
    Preview();

    void start();

private:
    Viewport viewport;
    Scene scene;
    ViewportControl viewportControl;
};

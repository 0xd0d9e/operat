#pragma once

#include "scene.h"
#include "stage.h"
#include "viewport_control.h"

class PreviewStage : public Stage
{
public:
    PreviewStage();

    void setViewport(Viewport* viewport) final;

private:
    Scene scene;
    ViewportControl viewportControl;
};


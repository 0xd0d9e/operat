#pragma once

#include "stage_manager.h"
#include "viewport.h"

class Engine : public StageManager
{
    Q_OBJECT
public:
    Engine();

    void start();

private:
    void initResources();

    Viewport viewport;
};

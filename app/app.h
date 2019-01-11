#pragma once

#include "stage_manager.h"
#include "viewport.h"

#include <QObject>

class App : public QObject
{
    Q_OBJECT
public:
    App();

    void start();

private:
    void initResources();

    Viewport viewport;
    StageManager stageManager;
};

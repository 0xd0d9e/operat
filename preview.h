#pragma once

#include "stage_manager.h"
#include "viewport.h"

#include <QObject>

class Preview : public QObject
{
    Q_OBJECT
public:
    Preview();

    void start();

private:
    void initResources();

    Viewport viewport;
    StageManager stageManager;
};

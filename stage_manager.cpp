#include "stage_manager.h"

#include "stage.h"

StageManager::StageManager(Viewport* viewport)
    : viewport(viewport)
{
}

Stage*StageManager::getCurrentStage() const
{
    return currentStage;
}

void StageManager::setCurrentStage(const QString& name)
{
    if (currentStage)
        currentStage->setViewport(nullptr);
    currentStage = stages.value(name, nullptr);
    if (currentStage)
        currentStage->setViewport(viewport);
}

void StageManager::addStage(const QString& name, Stage* stage)
{
    stages[name] = stage;
}

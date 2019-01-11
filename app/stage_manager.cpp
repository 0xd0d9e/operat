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
    setCurrentStage(stages.value(name, nullptr));
}

void StageManager::setCurrentStage(Stage* stage)
{
    if (stage == currentStage)
        return;

    if (currentStage)
        currentStage->setViewport(nullptr);

    currentStage = stage;

    if (currentStage)
        currentStage->setViewport(viewport);
}

void StageManager::addStage(const QString& name, Stage* stage)
{
    stages[name] = stage;
}

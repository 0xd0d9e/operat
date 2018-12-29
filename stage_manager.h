#pragma once

#include <QString>
#include <QMap>

class Stage;
class Viewport;

class StageManager
{
public:
    StageManager(Viewport* viewport);

    Stage* getCurrentStage() const;
    void setCurrentStage(const QString& name);

    void addStage(const QString& name, Stage* stage);

private:
    QMap<QString, Stage*> stages;
    Viewport* viewport = nullptr;
    Stage* currentStage = nullptr;
};

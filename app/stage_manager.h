#pragma once

#include <QString>
#include <QMap>
#include <QObject>

class Stage;
class Viewport;

class StageManager : public QObject
{
    Q_OBJECT
public:
    StageManager();

    void setViewport(Viewport* viewport);

    Stage* getCurrentStage() const;
    void setCurrentStage(Stage* stage);

    void addStage(const QString& name, Stage* stage);

public slots:
    void setCurrentStage(const QString& name);

private:
    QMap<QString, Stage*> stages;
    Viewport* viewport = nullptr;
    Stage* currentStage = nullptr;
};

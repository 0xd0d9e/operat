#pragma once

#include "common/simple_function.h"
#include "components/updater.h"
#include "stage.h"

class Button;
class Camera;

class MenuStage : public Stage
{
public:
    MenuStage();

    void addButton(const QString& text, SimpleFunction function);

    void setViewport(Viewport* viewport) final;

private:
    Viewport* viewport = nullptr;
    Updater updater;
    Camera* camera;
    double width = 0;
    double height = 0;
    double spacing = 20;
    double margin = 20;
};

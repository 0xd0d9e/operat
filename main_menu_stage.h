#pragma once

#include "common/button_function.h"
#include "components/scene.h"
#include "stage.h"

class Button;
class Camera;

class MainMenuStage : public Stage
{
public:
    MainMenuStage();

    void addButton(const QString& text, ButtonFunction function);

    void setViewport(Viewport* viewport) final;

private:
    std::list<Button*> buttons;
    Viewport* viewport = nullptr;
    Scene scene;
    Camera* camera;
    double width = 0;
    double height = 0;
    double spacing = 20;
    double margin = 20;
};

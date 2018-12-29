#pragma once

#include "button_function.h"
#include "scene.h"
#include "stage.h"
#include "viewport_listener.h"

class MenuButton;

class MainMenuStage : public Stage, public ViewportListener
{
public:
    MainMenuStage();

    void addButton(const QString& text, ButtonFunction function);

    void setViewport(Viewport* viewport) final;

private:
    void mouseMove(const ViewportMouseEvent &event) final;
    void mousePress(const ViewportMouseEvent &event) final;
    void mouseRelease(const ViewportMouseEvent &event) final;

    std::list<MenuButton*> buttons;
    Viewport* viewport = nullptr;
    Scene scene;
    double width = 0;
    double height = 0;
    double spacing = 20;
    double margin = 20;
    MenuButton* pressed = nullptr;
};

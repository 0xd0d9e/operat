#include "main_menu_stage.h"

#include "debug.h"
#include "scene.h"
#include "menu_button.h"
#include "viewport.h"
#include "viewport_mouse_event.h"

MainMenuStage::MainMenuStage()
{
}

void MainMenuStage::addButton(const QString& text, ButtonFunction function)
{
    if (height < margin)
        height = margin;

    if (height > margin)
        height += spacing;
    Component* root = scene.getRoot();
    MenuButton* button = root->create<MenuButton>(text, {{"preset", "menuButton"},
                                                         {"text", text},
                                                         {"function", toVariant(function)},
                                                         {"pos", QPointF(margin, height)}});
    const QRectF rect = button->getRect();
    width = std::max(rect.width(), width);
    height += rect.height();
    buttons.push_back(button);
}

void MainMenuStage::setViewport(Viewport* newViewport)
{
    if (viewport == newViewport)
        return;

    if (viewport)
    {
        viewport->setScene(nullptr);
        viewport->removeListener(this);
    }

    viewport = newViewport;

    if (viewport)
    {
        viewport->addListener(this);
        viewport->setScene(&scene);
        viewport->setViewRect({0, 0, width + margin * 2.0, height + margin});
    }
}

void MainMenuStage::mouseMove(const ViewportMouseEvent& event)
{
    if (pressed)
        return;
    for (MenuButton* button : buttons)
    {
        const bool hover = button->contains(QRectF(event.getScenePos(), QSizeF(1.0, 1.0)));
        button->setState(hover ? MenuButton::HighlightState : MenuButton::NormalState);
    }
}

void MainMenuStage::mousePress(const ViewportMouseEvent& event)
{
    if (pressed || event.getButton() != Qt::LeftButton)
        return;

    for (MenuButton* button : buttons)
    {
        if (button->contains(QRectF(event.getScenePos(), QSizeF(1.0, 1.0))))
        {
            pressed = button;
            button->setState(MenuButton::PressedState);
            break;
        }
    }
}

void MainMenuStage::mouseRelease(const ViewportMouseEvent& event)
{
    Q_UNUSED(event);
    if (pressed)
    {
        if (pressed->contains(QRectF(event.getScenePos(), QSizeF(1.0, 1.0))))
            pressed->getFunction()();
        pressed->setState(MenuButton::NormalState);
        pressed = nullptr;
    }
}

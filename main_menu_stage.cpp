#include "main_menu_stage.h"

#include "common/debug.h"
#include "components/button.h"
#include "components/camera.h"
#include "components/scene.h"
#include "events/event.h"
#include "events/invoke_event.h"
#include "events/mouse_event.h"
#include "viewport.h"

MainMenuStage::MainMenuStage()
{
    camera = scene.create<Camera>();
    camera->setScene(&scene);
}

void MainMenuStage::addButton(const QString& text, ButtonFunction function)
{
    if (height < margin)
        height = margin;

    if (height > margin)
        height += spacing;

    Button* button = scene.create<Button>(text, {{"preset", "menuButton"},
                                                 {"text", text},
                                                 {"function", toVariant(function)},
                                                 {"pos", QPointF(margin, height)}});
    const QRectF rect = button->getRect();
    width = std::max(rect.width(), width);
    height += rect.height();
    buttons.push_back(button);
    camera->setViewRect({0, 0, width + margin * 2.0, height + margin});
}

void MainMenuStage::setViewport(Viewport* newViewport)
{
    if (viewport == newViewport)
        return;

    if (viewport)
    {
        viewport->setCamera(nullptr);
    }

    viewport = newViewport;
    scene.setEnabled(viewport != nullptr);

    if (viewport)
    {
        viewport->setCamera(camera);
    }
}
#include "menu_stage.h"

#include "common/debug.h"
#include "components/button.h"
#include "components/camera.h"
#include "components/updater.h"
#include "events/event.h"
#include "events/invoke_event.h"
#include "events/mouse_event.h"
#include "viewport.h"

MenuStage::MenuStage()
{
    camera = updater.create<Camera>("menuCamera", {{"viewRect", QRectF(0, 0, 100, 100)},
                                                   {"frameSize", QSizeF(100, 100)}});
    camera->setScene(&updater);
}

void MenuStage::addButton(const QString& text, SimpleFunction function)
{
    if (height < margin)
        height = margin;

    if (height > margin)
        height += spacing;

    Button* button = updater.create<Button>(text, {{"preset", "menuButton"},
                                                   {"text", text},
                                                   {"function", toVariant(function)},
                                                   {"pos", QPointF(margin, height)}});
    const QRectF rect = button->getRect();
    width = std::max(rect.width(), width);
    height += rect.height();
    camera->setViewRect({0, 0, width + margin * 2.0, height + margin});
}

void MenuStage::setViewport(Viewport* newViewport)
{
    if (viewport == newViewport)
        return;

    if (viewport)
    {
        viewport->setCamera(nullptr);
    }

    viewport = newViewport;
    updater.setEnabled(viewport != nullptr);

    if (viewport)
    {
        viewport->setCamera(camera);
    }
}

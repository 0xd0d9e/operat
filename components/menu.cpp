#include "menu.h"

#include "button.h"

void Menu::addButton(const QString& text, SimpleFunction function)
{
    const double margin = getMargin();
    const double spacing = getSpacing();
    const QRectF rect = getRect();
    double width = rect.width();
    double height = rect.height();

    if (height < margin)
        height = margin;

    if (height > margin)
        height += spacing;

    Button* button = create<Button>(text, {{"preset", "menuButton"},
                                           {"text", text},
                                           {"function", toVariant(function)},
                                           {"pos", QPointF(margin, height)}});
    const QRectF buttonRect = button->getRect();
    width = std::max(buttonRect.width(), width);
    height += buttonRect.height();
    setRect({0, 0, width + margin * 2.0, height + margin});
}


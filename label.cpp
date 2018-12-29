#include "label.h"

#include "debug.h"

Label::Label(Component* parent, const QString& name, const QVariantMap& properties)
    : Shape(parent, name, properties)
{

}

void Label::paintComponent(QPainter* painter, const QRectF& sceneRect)
{
    Shape::paintComponent(painter, sceneRect);
    const QStringList text = getText();
    if (text.isEmpty())
        return;

    double height = painter->fontMetrics().height() + painter->fontMetrics().lineSpacing();
    double y = height;
    for (QString line : text)
    {
        painter->drawText(0, y, line);
        y += height;
    }
}

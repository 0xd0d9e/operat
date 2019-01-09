#include "label.h"

#include "common/debug.h"

Label::Label(Component* parent, const QString& name, const QVariantMap& properties)
    : Shape(parent, name, properties)
{
    updateRect(getText(), getFont());
}

void Label::paintComponent(QPainter* painter, const QRectF& sceneRect)
{
    Shape::paintComponent(painter, sceneRect);

    painter->setFont(getFont());
    painter->setPen(QPen(getColor()));
    painter->drawText(getTextRect(), getTextAlign(), getText());
}

void Label::onTextChanged(const QString& text)
{
    updateRect(text, getFont());
}

void Label::onFontChanged(const QFont& font)
{
    updateRect(getText(), font);
}

void Label::updateRect(const QString& text, const QFont& font)
{
    const int widthLimit = 1000;
    QFontMetrics fm(font);
    QRectF rect = fm.boundingRect(QRect(0, 0, widthLimit, 0), Qt::TextWordWrap, text);
    const double margin = getMargin();
    rect.moveTopLeft(QPointF(margin,margin));
    rect.setWidth(std::max(getMinimumWidth() - margin * 2.0, rect.width()));
    setTextRect(rect);
    rect.moveTopLeft(QPointF(0, 0));
    rect.setWidth(rect.width() + margin * 2.0);
    rect.setHeight(rect.height() + margin * 2.0);
    setRect(rect);
}

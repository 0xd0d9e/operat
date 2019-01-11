#pragma once

#include "shape.h"

#include <QFont>

class Label : public Shape
{
public:
    DECLARE_CONSTRUCTOR(Label, Shape)

    DECLARE_PROPERTY_C(QString, text, Text, onTextChanged)
    DECLARE_PROPERTY(QColor, color, Color)
    DECLARE_PROPERTY_C(QFont, font, Font, onFontChanged)
    DECLARE_PROPERTY_D(double, margin, Margin, 0.0)
    DECLARE_PROPERTY(QRectF, textRect, TextRect)
    DECLARE_PROPERTY_D(int, textAlign, TextAlign, Qt::AlignLeft)
    DECLARE_PROPERTY_D(double, minimumWidth, MinimumWidth, 0.0)

    void paintComponent(QPainter *painter, const QRectF &sceneRect) override;

protected:
    void init() override;

private:
    void onTextChanged(const QString& text);
    void onFontChanged(const QFont& font);
    void updateRect(const QString& text, const QFont& font);
};

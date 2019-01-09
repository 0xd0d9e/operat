#pragma once

#include "shape.h"

#include <QFont>

class Label : public Shape
{
public:
    Label(Component* parent = nullptr, const QString& name = QString(), const QVariantMap& properties = QVariantMap());

    DECLARE_PROPERTY_C(QString, text, Text, onTextChanged)
    DECLARE_PROPERTY(QColor, color, Color)
    DECLARE_PROPERTY_C(QFont, font, Font, onFontChanged)
    DECLARE_PROPERTY_D(double, margin, Margin, 0.0)
    DECLARE_PROPERTY(QRectF, textRect, TextRect)
    DECLARE_PROPERTY_D(int, textAlign, TextAlign, Qt::AlignLeft)
    DECLARE_PROPERTY_D(double, minimumWidth, MinimumWidth, 0.0)

    void paintComponent(QPainter *painter, const QRectF &sceneRect) override;

private:
    void onTextChanged(const QString& text);
    void onFontChanged(const QFont& font);
    void updateRect(const QString& text, const QFont& font);
};

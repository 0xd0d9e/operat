#pragma once

#include "common/simple_function.h"
#include "shape.h"

#include <QRectF>

class Menu : public Shape
{
public:
    DECLARE_CONSTRUCTOR(Menu, Shape)

    DECLARE_PROPERTY_D(double, spacing, Spacing, 20.0)
    DECLARE_PROPERTY_D(double, margin, Margin, 20.0)

    void addButton(const QString& text, SimpleFunction function);

};


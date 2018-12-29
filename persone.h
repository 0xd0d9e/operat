#pragma once

#include "component.h"
#include "shape.h"

class Persone : public Component
{
public:
    Persone(Component* parent = nullptr, const QString& name = QString(), const QVariantMap& properties = QVariantMap());

    DECLARE_PROPERTY(QString, group, Group)

private:
    Shape* body;
    Shape* lhand;
    Shape* rhand;
};

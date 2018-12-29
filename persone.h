#pragma once

#include "component.h"
#include "shape.h"

class Persone : public Component
{
public:
    enum Dir
    {
        Left,
        Right,
        Top,
        Down
    };

    Persone(Component* parent = nullptr, const QString& name = QString(), const QVariantMap& properties = QVariantMap());

    DECLARE_PROPERTY(QString, group, Group)

    void update(const double time) override;

private:
    void rotate();

    Shape* body;
    Shape* lhand;
    Shape* rhand;
};

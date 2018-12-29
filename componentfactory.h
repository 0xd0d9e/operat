#pragma once

#include "component.h"

class ComponentFactory : public Component
{
public:
    using CreateFunction = std::function<Component*(const QString& name, Component* parent)>;

    ComponentFactory(Component* parent = nullptr);
    virtual ~ComponentFactory() = default;

    void registerType(const QString& type, CreateFunction function);
    virtual Component* create(const QString& type, Component* parent = nullptr, const QString& name = QString());
    virtual Component* create(const QString& type, const QString& name, Component* parent = nullptr);

    static ComponentFactory* getFactory(Component* parent);

private:
    std::map<QString,CreateFunction> functions;
};

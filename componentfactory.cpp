#include "componentfactory.h"

const char defaultFactoryName [] = ".default_factory";

ComponentFactory::ComponentFactory(Component* parent)
    : name(defaultFactoryName)
{
    parent->addChild(this);
}

void ComponentFactory::registerType(const QString& type, ComponentFactory::CreateFunction function)
{
    functions[type] = function;
}

Component* ComponentFactory::create(const QString& type, Component* parent, const QString& name)
{
    return createComponent(type, name, parent);
}

Component* ComponentFactory::create(const QString& type, const QString& name)
{
    const auto iter = functions.find(type);
    return iter == functions.end()
            ? nullptr
            : (*iter)(name, parent);
}

ComponentFactory* ComponentFactory::getFactory(Component* parent)
{
    return parent ? parent->get<ComponentFactory>(defaultFactoryName)
                  : nullptr;
}

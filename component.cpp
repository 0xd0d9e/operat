#include "component.h"

#include "debug.h"
#include "event.h"
#include "resource_manager.h"

Component::Component(Component* parent, const QString& name, const QVariantMap& properties)
    : properties(properties)
    , name(name)
{
    if (!properties.empty())
        applyPreset();

    if (parent)
        parent->addChild(this);
}

Component::~Component()
{
    Q_ASSERT(flags == NoGuardFlags);

    if (parent)
        parent->removeChild(this);
    clear();
}

Component*Component::getParent() const
{
    return parent;
}

void Component::setParent(Component* newParent)
{
    if (newParent == parent)
        return;

    if (parent)
        parent->removeChild(this);

    if (newParent)
        newParent->addChild(this);
}

QString Component::getName() const
{
    return name;
}

void Component::setName(const QString& newName)
{
    if (newName == name)
        return;

    name = newName;
}

QVariantMap Component::getProperties() const
{
    return properties;
}

void Component::setProperties(const QVariantMap& properties)
{
    this->properties = properties;
}

QPointF Component::getPos() const
{
    return pos;
}

void Component::setPos(const QPointF& pos)
{
    this->pos = pos;
}

double Component::getScale() const
{
    return scale;
}

void Component::setScale(const double scale)
{
    this->scale = scale;
}

void Component::addChild(Component* child)
{
    Q_ASSERT(child);

    if (child->parent)
        child->parent->removeChild(child);
    children.push_back(child);
    child->parent = this;
}

void Component::removeChild(Component* child)
{
    Q_ASSERT(child);

    if (child->parent != this)
        return;
    children.erase(std::find(children.begin(), children.end(), child));
    child->parent = nullptr;
}

void Component::clear()
{
    for (Component* child : children)
    {
        child->parent = 0;
        delete child;
    }
    children.clear();
}

Component* Component::getRoot()
{
    return parent ? parent->getRoot()
                  : this;
}

Component* Component::operator [](const QString& name)
{
    auto iter = std::find_if(children.begin(), children.end(), [name](Component* component)
    {
        return component->name == name;
    });
    return iter == children.end() ? nullptr : *iter;
}

bool Component::contains(const QRectF& sceneRect) const
{
    return sceneRect.contains(pos);
}

void Component::update(const double time)
{
    flags |= UpdateFlag;
    const int elapsed = floor(1000 * time);
    auto iter = events.begin();
    while (iter != events.end())
    {
        Event* event = *iter;
        if (event->prepare(elapsed))
        {
            iter = events.erase(iter);
            delete event;
        }
        else
        {
            ++iter;
        }
    }

    for (Component* child : children)
        child->update(time);

    flags ^= UpdateFlag;
}

void Component::paint(QPainter* painter, const QRectF& sceneRect)
{
    flags |= PaintFlag;
    painter->save();
    paintComponent(painter, sceneRect);
    for (Component* child : children)
    {
        child->paint(painter, sceneRect);
    }
    painter->restore();
    flags ^= PaintFlag;
}

void Component::dump(const int offset)
{
    const QString offsetStr(offset, QChar(' '));
    qDebug("%s%s(%s)", qPrintable(offsetStr), typeid(this).name(), qPrintable(name));
    qDebug("%s  x: %f, y: %f, rotation: %f", qPrintable(offsetStr), pos.x(), pos.y(), rotation);
    qDebug() << "properties" << properties;
    if (!children.empty())
    {
        qDebug("%s  childs(%lu)", qPrintable(offsetStr), children.size());
        for (Component* child : children)
        {
            child->dump(offset + 2);
        }
    }
}

void Component::addEvent(Event* event)
{
    events.push_back(event);
}

void Component::paintComponent(QPainter* painter, const QRectF& sceneRect)
{
    Q_UNUSED(sceneRect);

    QTransform transform = painter->transform();
    transform.translate(pos.x(), pos.y());
    transform.rotateRadians(rotation);
    transform.scale(scale, scale);
    painter->setTransform(transform);
}

void Component::applyPreset()
{
    const auto iter = properties.find("preset");
    if (iter == properties.end())
        return;

    applyPreset(iter.value().toString());
}

void Component::applyPreset(const QString& name)
{
    const auto& resourceManager = ResourceManager::instance();

    const auto preset = resourceManager.getPreset(name);
    if (preset.empty())
        return;

    QStringList presets = properties["presets"].toStringList();
    if (presets.contains(name))
    {
        qCritical("Detected recursive presets link '%s' to %s", qPrintable(presets.join("->")), qPrintable(name));
        return;
    }
    presets.append(name);
    applyPreset(preset);
}

void Component::applyPreset(const QVariantMap& preset)
{
    const auto parentIter = preset.find("preset");
    if (parentIter != preset.end())
    {
        applyPreset(parentIter.value().toString());
    }

    for (auto iter = preset.begin(), end = preset.end(); iter != end; ++iter)
    {
        properties[iter.key()] = iter.value();
    }
}

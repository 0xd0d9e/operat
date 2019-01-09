#include "component.h"

#include "common/debug.h"
#include "events/event.h"
#include "events/invoke_event.h"
#include "resource_manager.h"

#include <cmath>

Component::Component(Component* parent, const QString& name, const QVariantMap& properties)
    : properties(properties)
{
    if (!properties.contains(scaleKey()))
        setScale(1.0);
    if (!properties.contains(rotationKey()))
        setRotation(0.0);

    if (!name.isEmpty())
        setName(name);
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

QVariantMap Component::getProperties() const
{
    return properties;
}

void Component::setProperties(const QVariantMap& properties)
{
    this->properties = properties;
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
    return find(name);
}

Component* Component::find(const QString& name)
{
    auto iter = std::find_if(children.begin(), children.end(), [name](Component* component)
    {
        return component->getName() == name;
    });
    return iter == children.end() ? nullptr : *iter;
}

bool Component::contains(const QRectF& sceneRect) const
{
    return sceneRect.contains(parent ? parent->localToGlobal(getPos()) : getPos());
}

void Component::update(const double time)
{
    flags |= UpdateFlag;
    prepareEvents(time);

    auto iter = children.begin();
    while (iter != children.end())
    {
        Component* child = *iter;
        child->update(time);
        if (child->flags & DeleteLater)
        {
            iter = children.erase(iter);
            child->parent = nullptr;
            child->flags ^= DeleteLater;
            delete child;
        }
        else
        {
            ++iter;
        }
    }

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

size_t Component::getChildCount() const
{
    return children.size();
}

void Component::dump(const int offset) const
{
    const QString offsetStr(offset, QChar(' '));
    qDebug("%s%s(%s)", qPrintable(offsetStr), typeid(this).name(), qPrintable(getName()));
    qDebug("  properties(%d):", properties.size());
    for (auto c = properties.begin(), e = properties.end(); c != e; ++c)
    {
        qDebug() << "  " << c.key() << ":" << c.value();
    }
    if (!children.empty())
    {
        qDebug("%s  childs(%lu)", qPrintable(offsetStr), children.size());
        for (Component* child : children)
        {
            child->dump(offset + 2);
        }
    }
}

void Component::postEvent(Event* event)
{
    events.push_back(event);
}

QPointF Component::localToParent(const QPointF& localPos) const
{
    const QPointF pos = getPos();
    const double scale = getScale();

    QTransform transform;
    transform.translate(pos.x(), pos.y());
    transform.rotateRadians(getRotation());
    transform.scale(scale, scale);
    return transform.map(localPos);
}

QRectF Component::localToParent(const QRectF& localRect) const
{
    const QPointF pos = getPos();
    const double scale = getScale();

    QTransform transform;
    transform.translate(pos.x(), pos.y());
    transform.rotateRadians(getRotation());
    transform.scale(scale, scale);
    return transform.mapRect(localRect);
}

QPointF Component::localToGlobal(const QPointF& localPos) const
{
    return parent ? parent->localToGlobal(localToParent(localPos))
                  : localToParent(localPos);
}

QRectF Component::localToGlobal(const QRectF& localRect) const
{
    return parent ? parent->localToGlobal(localToParent(localRect))
                  : localToParent(localRect);
}

void Component::deleteLater()
{
    if (flags & UpdateFlag || (parent && (parent->flags & UpdateFlag)))
    {
        flags |= DeleteLater;
    }
    else
    {
        delete this;
    }
}

void Component::paintComponent(QPainter* painter, const QRectF& sceneRect)
{
    Q_UNUSED(sceneRect);

    const QPointF pos = getPos();
    const double scale = getScale();

    QTransform transform = painter->transform();
    transform.translate(pos.x(), pos.y());
    transform.rotateRadians(getRotation());
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
    properties["presets"] = presets;
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

void Component::prepareEvent(Event* event, const int elapsed)
{
    if (event->getType() == Event::Invoke)
    {
        static_cast<InvokeEvent*>(event)->exec(elapsed);
    }
    else
    {
        for (Component* child : children)
        {
            child->prepareEvent(event, elapsed);
        }
    }
}

void Component::prepareEvents(const double time)
{
    const int elapsed = ::floor(1000.0 * time);
    auto iter = events.begin();
    while (iter != events.end())
    {
        Event* event = *iter;
        prepareEvent(event, elapsed);
        if (event->isComplete())
        {
            iter = events.erase(iter);
            delete event;
        }
        else
        {
            ++iter;
        }
    }
}

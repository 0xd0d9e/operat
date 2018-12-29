#pragma once

#include "default_value.h"

#include <QPainter>
#include <QString>
#include <QVariantMap>

#include <vector>
#include <list>

#define DECLARE_PROPERTY_CD(Type, name, Name, onChange, byDefault) \
    static const char* name##Key() { return #name; } \
    Type get##Name(const Type& defaultValue = byDefault) const { return properties.value(#name, QVariant::fromValue(defaultValue)).value< Type >(); } \
    void set##Name(const Type& value) { properties[#name] = QVariant::fromValue(value); onChange(value); }

#define DECLARE_PROPERTY_D(Type, name, Name, byDefault) \
    DECLARE_PROPERTY_CD(Type, name, Name, on##Name##Changed, byDefault) \
    void on##Name##Changed(const Type&) {}

#define DECLARE_PROPERTY_C(Type, name, Name, onChange) \
    DECLARE_PROPERTY_CD(Type, name, Name, onChange, defaultValue<Type>())

#define DECLARE_PROPERTY(Type, name, Name) \
    DECLARE_PROPERTY_C(Type, name, Name, on##Name##Changed) \
    void on##Name##Changed(const Type&) {}

#define DECLARE_CONSTRUCTOR(Type, Super) \
    Type(Component* parent = nullptr, const QString& name = QString(), const QVariantMap& properties = QVariantMap()) : Super(parent, name, properties) {}

class Event;

class Component
{
public:
    Component(Component* parent = nullptr, const QString& name = QString(), const QVariantMap& properties = QVariantMap());
    virtual ~Component();

    Component* getParent() const;
    void setParent(Component* component);

    template <typename Type>
    void onChanged(const Type&) {}

    DECLARE_PROPERTY(QString, name, Name)
    DECLARE_PROPERTY(QPointF, pos, Pos)
    DECLARE_PROPERTY(double, scale, Scale)
    DECLARE_PROPERTY(double, rotation, Rotation)

    QVariantMap getProperties() const;
    void setProperties(const QVariantMap& properties);

    void addChild(Component* child);
    void removeChild(Component* child);
    void clear();

    Component* getRoot();

    Component* operator [] (const QString& name);

    virtual bool contains(const QRectF& sceneRect) const;

    virtual void update(const double time);
    virtual void paint(QPainter* painter, const QRectF& sceneRect);

    template <typename Type>
    Type* get(const QString& name);

    size_t getChildCount() const;

    template <typename Function>
    void forEach(Function function);
    template <typename BeginFunction, typename EndFunction>
    void forEach(BeginFunction begin, EndFunction end);

    template <typename Type>
    Type* create(const QString& name = QString(), const QVariantMap& properties = QVariantMap());

    void dump(const int offset = 0) const;

    void addEvent(Event* event);

    QPointF localToParent(const QPointF& localPos) const;
    QRectF localToParent(const QRectF& localRect) const;

    QPointF localToGlobal(const QPointF& localPos) const;
    QRectF localToGlobal(const QRectF& localRect) const;
protected:
    virtual void paintComponent(QPainter* painter, const QRectF& sceneRect);
    void applyPreset();
    void applyPreset(const QString& name);
    void applyPreset(const QVariantMap& preset);

    QVariantMap properties;

private:
    enum GuardFlags
    {
        NoGuardFlags = 0,
        UpdateFlag = 1,
        PaintFlag = 2
    };

    Component* parent = nullptr;
    std::vector<Component*> children;
    std::list<Event*> events;
    int flags = NoGuardFlags;
};


template <typename Type>
Type* Component::get(const QString& name)
{
    return reinterpret_cast<Type*>(operator [](name));
}

template <typename Function>
void Component::forEach(Function function)
{
    function(this);
    for (Component* child : children)
    {
        child->forEach(function);
    }
}
template <typename BeginFunction, typename EndFunction>
void Component::forEach(BeginFunction begin, EndFunction end)
{
    begin(this);
    for (Component* child : children)
    {
        child->forEach(begin, end);
    }
    end(this);
}

template <typename Type>
Type* Component::create(const QString& name, const QVariantMap& properties)
{
    return new Type(this, name, properties);
}

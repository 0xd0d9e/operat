#pragma once

#include "common/default_value.h"

#include <QPainter>
#include <QString>
#include <QVariantMap>

#include <vector>
#include <list>
#include <functional>

/// Declare property \a name (\a Name) of \a type with change handler \a onChange and default value of \a byDefault
#define DECLARE_PROPERTY_CD(Type, name, Name, onChange, byDefault) \
    static const char* name##Key() { return #name; } \
    Type get##Name(const Type& defaultValue = byDefault) const { return properties.value(#name, QVariant::fromValue(defaultValue)).value< Type >(); } \
    void set##Name(const Type& value) { properties[#name] = QVariant::fromValue(value); onChange(value); }

/// Declare property \a name (\a Name) of \a type with default value of \a byDefault
#define DECLARE_PROPERTY_D(Type, name, Name, byDefault) \
    DECLARE_PROPERTY_CD(Type, name, Name, on##Name##Changed, byDefault) \
    void on##Name##Changed(const Type&) {}

/// Declare property \a name (\a Name) of \a type with change handler \a onChange
#define DECLARE_PROPERTY_C(Type, name, Name, onChange) \
    DECLARE_PROPERTY_CD(Type, name, Name, onChange, defaultValue<Type>())

/// Declare property \a name (\a Name) of \a type
#define DECLARE_PROPERTY(Type, name, Name) \
    DECLARE_PROPERTY_C(Type, name, Name, on##Name##Changed) \
    void on##Name##Changed(const Type&) {}

/// Declare initialization constructor for \a Type with \a Super parent Component
#define DECLARE_CONSTRUCTOR(Type, Super) \
    Type(Component* parent = nullptr, const QString& name = QString(), const QVariantMap& properties = QVariantMap()) : Super(parent, name, properties) {init();}

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
    DECLARE_PROPERTY_D(double, scale, Scale, 1.0)
    DECLARE_PROPERTY_D(double, rotation, Rotation, 0.0)
    DECLARE_PROPERTY(double, minScale, MinScale)
    DECLARE_PROPERTY(double, maxScale, MaxScale)
    DECLARE_PROPERTY_D(bool, visible, Visible, true)

    QString getPath() const;
    bool isVisible() const;

    QVariantMap getProperties() const;
    void setProperties(const QVariantMap& properties);

    void addChild(Component* child);
    void removeChild(Component* child);
    void clear();

    Component* getRoot();

    Component* operator [] (const QString& name) const;
    Component* find(const QString& name) const;

    virtual bool contains(const QRectF& sceneRect) const;

    virtual void update(const double time);
    virtual void paint(QPainter* painter, const QRectF& sceneRect);

    template <typename Type>
    Type* get(const QString& name) const;

    size_t getChildCount() const;

    template <typename Function>
    void forEach(Function function);
    template <typename BeginFunction, typename EndFunction>
    void forEach(BeginFunction begin, EndFunction end);

    template <typename Type>
    Type* create(const QString& name = QString(), const QVariantMap& properties = QVariantMap());

    void dump(const int offset = 0) const;

    void postEvent(Event* event);

    QPointF localToParent(const QPointF& localPos) const;
    QRectF localToParent(const QRectF& localRect) const;

    QPointF localToGlobal(const QPointF& localPos) const;
    QRectF localToGlobal(const QRectF& localRect) const;

    template <typename Type>
    Type* cast() { return static_cast<Type*>(this); }
    template <typename Type>
    const Type* cast() const { return static_cast<const Type*>(this); }

    void deleteLater();

protected:
    virtual void init();
    virtual void paintComponent(QPainter* painter, const QRectF& sceneRect);

    /// read and apply preset
    void applyPreset();
    /// find and apply preset
    void applyPreset(const QString& name);
    /// copy properties from preset
    void applyPreset(const QVariantMap& preset);
    /// return true if event is complete
    virtual bool prepareEvent(Event* event, const int elapsed);

    bool checkLod(const double scale);

    QVariantMap properties;

private:
    void prepareEvents(const double time);

    enum GuardFlags
    {
        NoGuardFlags = 0,
        UpdateFlag = 1,
        PaintFlag = 2,
        DeleteLater = 4
    };

    Component* parent = nullptr;
    std::vector<Component*> children;
    std::list<Event*> events;
    int flags = NoGuardFlags;
};


template <typename Type>
Type* Component::get(const QString& name) const
{
    return reinterpret_cast<Type*>(find(name));
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

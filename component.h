#pragma once

#include <QPainter>
#include <QString>
#include <QVariantMap>

#define DECLARE_PROPERTY(Type, name, Name) \
    static const char* name##Key() { return #name; } \
    Type get##Name() const { return properties[#name].value<Type>(); } \
    void set##Name(const Type& value) { properties[#name] = QVariant::fromValue(value); }

class Component
{
public:
    Component(Component* parent = nullptr, const QString& name = QString(), const QVariantMap& properties = QVariantMap());
    virtual ~Component();

    Component* getParent() const;
    void setParent(Component* component);

    QString getName() const;
    void setName(const QString& value);

    QVariantMap getProperties() const;
    void setProperties(const QVariantMap& properties);

    QPointF getPos() const;
    void setPos(const QPointF& pos);

    double getScale() const;
    void setScale(const double scale);

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

    template <typename Function>
    void forEach(Function function);
    template <typename BeginFunction, typename EndFunction>
    void forEach(BeginFunction begin, EndFunction end);

    template <typename Type>
    Type* create(const QString& name = QString(), const QVariantMap& properties = QVariantMap());

    void dump(const int offset = 0);

protected:
    virtual void paintComponent(QPainter* painter, const QRectF& sceneRect);
    void applyPreset();
    void applyPreset(const QString& name);
    void applyPreset(const QVariantMap& preset);

    QVariantMap properties;

private:
    Component* parent = nullptr;
    QString name;
    QPointF pos;
    /// in radians
    double rotation = 0.0;
    double scale = 1.0;
    std::vector<Component*> children;
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

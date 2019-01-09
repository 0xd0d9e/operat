#pragma once

#include <QBrush>
#include <QDebug>
#include <QMetaType>
#include <QPen>
#include <QVariant>

class QPainter;

class Style
{
public:
    Style(const QPen& pen = QPen(), const QBrush& brush = QBrush());
    Style(const QBrush& brush, const QPen& pen = QPen());

    QPen getPen() const;
    void setPen(const QPen& value);

    QBrush getBrush() const;
    void setBrush(const QBrush& value);

    void apply(QPainter* painter);

    operator QVariant() const { return QVariant::fromValue(*this); }

private:
    QPen pen;
    QBrush brush;
};

Q_DECLARE_METATYPE(Style)

inline QDebug operator << (QDebug stream, const Style& style)
{
    stream.nospace() << "Style(" << style.getPen() << "," << style.getBrush() << ")";
    return stream;
}

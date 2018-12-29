#pragma once

#include "component.h"

#include <QElapsedTimer>
#include <QPainter>
#include <QTimer>

class Scene : public QObject
{
    Q_OBJECT
public:
    Scene(QObject* parent = 0);

    Component* getRoot() const;

    void paint(QPainter* painter, const QRectF& sceneRect);

private slots:
    void update();

private:
    Component* root;
    int updateCount = 0;
    QElapsedTimer timer;
    QTimer updateTimer;
};

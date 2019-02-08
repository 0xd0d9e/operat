#pragma once

#include "component.h"

#include <QElapsedTimer>
#include <QPainter>
#include <QTimer>

class Updater : public QObject, public Component
{
    Q_OBJECT
public:
    Updater(QObject* parent = 0);

    bool isEnabled() const;

public slots:
    void setEnabled(const bool enabled);

private slots:
    void update();

private:
    int updateCount = 0;
    QElapsedTimer timer;
    QTimer updateTimer;
};

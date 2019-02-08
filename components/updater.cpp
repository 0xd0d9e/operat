#include "updater.h"

#include "common/config.h"
#include "common/debug.h"

#include <QTextBrowser>
#include <QTimer>

Updater::Updater(QObject* parent)
    : QObject(parent)
    , Component(nullptr, "root")
{
    init();
    updateTimer.setInterval(Config::updateInterval);
    connect(&updateTimer, &QTimer::timeout, this, &Updater::update);
}

bool Updater::isEnabled() const
{
    return updateTimer.isActive();
}

void Updater::setEnabled(const bool enabled)
{
    if (isEnabled() == enabled)
        return;

    if (enabled)
    {
        updateTimer.start();
        timer.start();
    }
    else
    {
        updateTimer.stop();
    }
}

void Updater::update()
{
    Component::update(Config::updateScale);
    ++updateCount;
}

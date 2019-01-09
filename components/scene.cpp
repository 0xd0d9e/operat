#include "scene.h"

#include "common/config.h"
#include "common/debug.h"

#include <QTextBrowser>
#include <QTimer>

Scene::Scene(QObject* parent)
    : QObject(parent)
    , Component(nullptr, "root")
{
    updateTimer.setInterval(Config::updateInterval);
    connect(&updateTimer, &QTimer::timeout, this, &Scene::update);
}

bool Scene::isEnabled() const
{
    return updateTimer.isActive();
}

void Scene::setEnabled(const bool enabled)
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

void Scene::update()
{
    Component::update(Config::updateScale);
    ++updateCount;
}

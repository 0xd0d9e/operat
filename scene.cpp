#include "scene.h"

#include "config.h"
#include "debug.h"

#include <QTextBrowser>
#include <QTimer>

Scene::Scene(QObject* parent) : QObject(parent)
    , root(new Component(nullptr, "root"))
{
    updateTimer.setInterval(Config::updateInterval);
    connect(&updateTimer, &QTimer::timeout, this, &Scene::update);

    updateTimer.start();
    timer.start();
}

Component*Scene::getRoot() const
{
    return root;
}

void Scene::paint(QPainter* painter, const QRectF& sceneRect)
{
    root->paint(painter, sceneRect);
}

void Scene::update()
{
    root->update(Config::updateScale);
    ++updateCount;
}

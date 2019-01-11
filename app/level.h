#pragma once

#include <QRectF>

class Scene;
class Persone;

class Level
{
public:
    Level(const double tileSize);

    Scene* getScene() const;

    void addPersone(Persone* persone);

private:
    double tileSize;
    Scene* scene = nullptr;
    QRectF rect;
};

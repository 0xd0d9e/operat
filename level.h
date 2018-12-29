#pragma once

class Scene;
class Persone;

class Level
{
public:
    Level();

    void setScene(Scene* scene);

    void addPersone(Persone* persone);

private:
    Scene* scene = nullptr;
};

#pragma once

class Scene;
class Persone;

class ObjectManager
{
public:
    ObjectManager();

    void setScene(Scene* scene);

    void addPersone(Persone* persone);

private:
    Scene* scene = nullptr;
};

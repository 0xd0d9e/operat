#pragma once

class Scene;
class Updater;
class Viewport;

class SceneManager
{
public:
    SceneManager();
    virtual ~SceneManager();

    void setViewport(Viewport* viewport);

    Scene* getScene() const;
    void setScene(Scene* scene);

private:
    Scene* scene = nullptr;
    Updater* updater = nullptr;
    Viewport* viewport = nullptr;
};

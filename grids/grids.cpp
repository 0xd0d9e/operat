#include "grids.h"

#include "app/viewport.h"
#include "common/utils.h"
#include "components/camera.h"
#include "components/menu.h"
#include "events/event_condition.h"
#include "events/event_watcher.h"
#include "events/key_event.h"

#include <QCoreApplication>


void Char::init()
{
    create<Shape>("body", {{"type", Shape::Ellipse},
                           {"style", Style(QPen(Qt::black, 0), QBrush("#ffaaaa"))},
                           {"rect", makeRect(25, 25)}});
}



GridsScene::GridsScene(GridsLogic* grids)
    : grids(grids)
    , cameraControl(new CameraControl())
{
    setName("mainScene");

    Menu* menu = create<Menu>("menu");
    menu->addButton("Continue", [menu](){menu->setVisible(false);});
    menu->addButton("Exit", [this](){this->grids->exit();});
    menu->setVisible(false);

    create<Camera>("camera", {{"viewRect", QRectF(0, 0, 800, 600)}});
    cameraControl->setCamera(getCamera());

    create<EventWatcher>()->addCondition(Event::KeyPress, new KeyEventCondition(Qt::Key_Escape), [menu](Event*)
    {
        menu->setVisible(true);
        return true;
    });

    create<Char>("char1", {{"pos", QPointF(100, 10)}});
    create<Char>("char2", {{"pos", QPointF(100, 100)}});
}

Camera* GridsScene::getCamera() const
{
    return get<Camera>("camera");
}

GridsMenuScene::GridsMenuScene(GridsLogic* grids)
    : grids(grids)
{
    setName("menuScene");

    Menu* menu = create<Menu>("mainMenu");
    menu->addButton("Start", [this](){this->grids->start();});
    menu->addButton("Exit", [this](){this->grids->exit();});

    create<Camera>("camera", {{"viewRect", menu->getRect()}});
}

Camera* GridsMenuScene::getCamera() const
{
    return get<Camera>("camera");
}



GridsStage::GridsStage()
    : mainScene(this)
    , menuScene(this)
{
    sceneManager.setScene(&mainScene);
}

void GridsStage::setViewport(Viewport* viewport)
{
    sceneManager.setViewport(viewport);
}

void GridsStage::start()
{
    sceneManager.setScene(&mainScene);
}

void GridsStage::exit()
{
    qApp->quit();
}

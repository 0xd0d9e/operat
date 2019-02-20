#include "route_monitor_scene.h"

#include "route.h"
#include "route_monitor.h"

#include <components/camera.h>
#include <components/camera_control.h>
#include <components/grid.h>
#include <components/sprite.h>
#include <components/vehicle_control.h>

#include <events/event.h>
#include <events/event_watcher.h>
#include <events/key_event.h>
#include <events/mouse_event.h>

RouteMonitorScene::RouteMonitorScene() : cameraControl(new CameraControl())
{
    setName("mainScene");

    Component* ui = create<Component>("ui");

    Camera* camera = create<Camera>("camera", {{"viewRect", QRectF(0, 0, 800, 600)}});
    camera->setOverlay(ui);
    cameraControl->setCamera(getCamera());

    create<Sprite>("worldMap", {
        {"image", "WorldMap"},
        {"origin", QPointF(-0.5, -0.5)}
    });
    create<Grid>("grid", {{"size", 32}, {"pen", QPen(Qt::black)}});

    addChild(cameraControl);


    Route* route = create<Route>("route1", {{"lineStyle", Style(QPen(QColor("#aa9999"), 2))},
                                            {"pointStyle", Style(QPen(Qt::NoPen), QBrush(Qt::red))},
                                            {"pointWidth", 16}});

    Sprite* ship = create<Sprite>("ship", {{"image", "Ship"},
                                           {"origin", QPointF(-0.5, -0.5)},
                                           {"scale", 0.5}});


    camera->setFocused(ship);

    VehicleControl* shipControl = create<VehicleControl>("shipControl",
    {
        {"speed", 50.0},
        {"mode", VehicleControl::DirectionalMoving}
    });
    shipControl->setTarget(ship);

    RouteMonitor* routeMonitor = create<RouteMonitor>("routeMonitor");
    routeMonitor->setupUi(ui);
    routeMonitor->setRoute(route);
    routeMonitor->setShip(ship);
    routeMonitor->setEnabled(true);


    EventWatcher* watcher = create<EventWatcher>();
    watcher->addAction(Event::MousePress, [route, ship, routeMonitor](Event* event)
    {
        MouseEvent* mouseEvent = static_cast<MouseEvent*>(event);
        if (mouseEvent->getButton() != Qt::LeftButton)
            return false;

        if (mouseEvent->getModifiers() == Qt::ShiftModifier)
        {
            route->addPoint(mouseEvent->getScenePos(), 15.0, 10.0);
            routeMonitor->resetState();
        }
        else
        {
            ship->setPos(mouseEvent->getScenePos());
            routeMonitor->resetState();
        }
        return true;
    });

    watcher->addAction(Event::KeyPress, [route, routeMonitor](Event* event)
    {
        KeyEvent* keyEvent = static_cast<KeyEvent*>(event);
        if (keyEvent->getKey() == Qt::Key_Minus)
        {
            routeMonitor->setEnabled(false);
            route->clearPoints();
            routeMonitor->setEnabled(true);
            return true;
        }
        return false;
    });
}

Camera* RouteMonitorScene::getCamera() const
{
    return get<Camera>("camera");
}

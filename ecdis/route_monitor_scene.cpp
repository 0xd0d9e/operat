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
#include <events/mouse_event.h>

RouteMonitorScene::RouteMonitorScene() : cameraControl(new CameraControl())
{
    setName("mainScene");

    create<Camera>("camera", {{"viewRect", QRectF(0, 0, 800, 600)}});
    cameraControl->setCamera(getCamera());

    create<Grid>("grid", {{"size", 32}, {"pen", QPen(Qt::black)}});

    addChild(cameraControl);


    Route* route = create<Route>("route1", {{"lineStyle", Style(QPen(QColor("#aa9999"), 2))},
                                            {"pointStyle", Style(QPen(Qt::NoPen), QBrush(Qt::red))},
                                            {"pointWidth", 16}});

    Sprite* ship = create<Sprite>("ship", {{"image", "Ship"},
                                           {"origin", QPointF(-0.5, -0.5)},
                                           {"minScale", 0.25}});

    EventWatcher* watcher = create<EventWatcher>();
    watcher->addAction(Event::MousePress, [route, ship](Event* event)
    {
        MouseEvent* mouseEvent = static_cast<MouseEvent*>(event);
        if (mouseEvent->getButton() != Qt::LeftButton)
            return false;

        if (mouseEvent->getModifiers() == Qt::ControlModifier)
        {
            route->addPoint(mouseEvent->getScenePos(), 15.0, 10.0);
        }
        else
        {
            ship->setPos(mouseEvent->getScenePos());
        }
        return true;
    });

    VehicleControl* shipControl = create<VehicleControl>("shipControl", {{"speed", 100.0}});
    shipControl->setTarget(ship);

    RouteMonitor* routeMonitor = create<RouteMonitor>("routeMonitor");
    routeMonitor->setRoute(route);
    routeMonitor->setShip(ship);
    routeMonitor->setEnabled(true);
}

Camera* RouteMonitorScene::getCamera() const
{
    return get<Camera>("camera");
}

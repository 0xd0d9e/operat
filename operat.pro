QT += widgets

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    app/engine.cpp \
    app/main.cpp \
    app/menu_stage.cpp \
    app/message_service.cpp \
    app/resource_manager.cpp \
    app/service.cpp \
    app/service_manager.cpp \
    app/stage.cpp \
    app/stage_manager.cpp \
    app/store_service.cpp \
    app/viewport.cpp \
    common/grid_metrics.cpp \
    common/style.cpp \
    components/button.cpp \
    components/camera.cpp \
    components/camera_control.cpp \
    components/component.cpp \
    components/display.cpp \
    components/grid.cpp \
    components/label.cpp \
    components/line.cpp \
    components/menu.cpp \
    components/persone.cpp \
    components/scene.cpp \
    components/scene_manager.cpp \
    components/shape.cpp \
    components/sprite.cpp \
    components/updater.cpp \
    ecdis/route_monitor_scene.cpp \
    events/event.cpp \
    events/event_condition.cpp \
    events/event_listener.cpp \
    events/event_watcher.cpp \
    events/input_event.cpp \
    events/invoke_event.cpp \
    events/key_event.cpp \
    events/mouse_event.cpp \
    events/wheel_event.cpp \
    grids/grids.cpp \
    preview/preview_stage.cpp \
    ecdis/ecdis_stage.cpp \
    ecdis/route.cpp \
    components/vehicle_control.cpp \
    ecdis/route_monitor.cpp \
    ecdis/route_calculator.cpp \
    ecdis/voyage_parameters.cpp

HEADERS += \
    app/engine.h \
    app/menu_stage.h \
    app/message_service.h \
    app/resource_manager.h \
    app/service.h \
    app/service_manager.h \
    app/stage.h \
    app/stage_manager.h \
    app/store_service.h \
    app/viewport.h \
    common/config.h \
    common/debug.h \
    common/default_value.h \
    common/grid_metrics.h \
    common/simple_function.h \
    common/style.h \
    common/utils.h \
    components/button.h \
    components/camera.h \
    components/camera_control.h \
    components/component.h \
    components/display.h \
    components/grid.h \
    components/label.h \
    components/line.h \
    components/menu.h \
    components/persone.h \
    components/scene.h \
    components/scene_manager.h \
    components/shape.h \
    components/sprite.h \
    components/updater.h \
    ecdis/route_monitor_scene.h \
    events/event.h \
    events/event_condition.h \
    events/event_listener.h \
    events/event_watcher.h \
    events/input_event.h \
    events/invoke_event.h \
    events/key_event.h \
    events/mouse_event.h \
    events/wheel_event.h \
    grids/grids.h \
    preview/preview_stage.h \
    ecdis/ecdis_stage.h \
    ecdis/route.h \
    components/vehicle_control.h \
    ecdis/route_monitor.h \
    ecdis/voyage_state.h \
    common/geometry_math.h \
    ecdis/route_calculator.h \
    common/straight.h \
    ecdis/voyage_parameters.h

RESOURCES += \
    resources/resources.qrc


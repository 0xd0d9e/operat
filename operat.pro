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
    events/wheel_event.cpp \
    events/mouse_event.cpp \
    events/key_event.cpp \
    events/invoke_event.cpp \
    events/event.cpp \
    common/grid_metrics.cpp \
    common/style.cpp \
    preview/preview_stage.cpp \
    components/camera.cpp \
    components/grid.cpp \
    components/label.cpp \
    components/persone.cpp \
    components/shape.cpp \
    components/sprite.cpp \
    events/event_listener.cpp \
    components/button.cpp \
    components/camera_control.cpp \
    components/display.cpp \
    app/main.cpp \
    app/resource_manager.cpp \
    app/message_service.cpp \
    app/service.cpp \
    app/service_manager.cpp \
    app/store_service.cpp \
    components/component.cpp \
    app/menu_stage.cpp \
    app/stage.cpp \
    app/stage_manager.cpp \
    app/viewport.cpp \
    grids/grids.cpp \
    components/updater.cpp \
    components/menu.cpp \
    app/engine.cpp \
    events/input_event.cpp \
    events/event_condition.cpp \
    events/event_watcher.cpp \
    components/scene_manager.cpp \
    components/scene.cpp

HEADERS += \
    events/wheel_event.h \
    events/invoke_event.h \
    events/key_event.h \
    events/event.h \
    events/mouse_event.h \
    common/utils.h \
    common/style.h \
    common/config.h \
    common/debug.h \
    common/default_value.h \
    common/grid_metrics.h \
    preview/preview_stage.h \
    components/camera.h \
    components/grid.h \
    components/persone.h \
    components/shape.h \
    components/sprite.h \
    components/label.h \
    events/event_listener.h \
    components/button.h \
    components/camera_control.h \
    components/display.h \
    app/resource_manager.h \
    app/store_service.h \
    app/service_manager.h \
    app/service.h \
    app/message_service.h \
    app/stage.h \
    app/menu_stage.h \
    app/viewport.h \
    app/stage_manager.h \
    components/component.h \
    grids/grids.h \
    components/updater.h \
    components/menu.h \
    app/engine.h \
    events/input_event.h \
    events/event_condition.h \
    events/event_watcher.h \
    common/simple_function.h \
    components/scene_manager.h \
    components/scene.h

RESOURCES += \
    resources/resources.qrc


QT += widgets

CONFIG += c++11

OPERAT_SRC_PATH = $$PWD

INCLUDEPATH += $$OPERAT_SRC_PATH

SOURCES += \
    $$OPERAT_SRC_PATH/app/engine.cpp \
    $$OPERAT_SRC_PATH/app/menu_stage.cpp \
    $$OPERAT_SRC_PATH/app/message_service.cpp \
    $$OPERAT_SRC_PATH/app/resource_manager.cpp \
    $$OPERAT_SRC_PATH/app/service.cpp \
    $$OPERAT_SRC_PATH/app/service_manager.cpp \
    $$OPERAT_SRC_PATH/app/stage.cpp \
    $$OPERAT_SRC_PATH/app/stage_manager.cpp \
    $$OPERAT_SRC_PATH/app/store_service.cpp \
    $$OPERAT_SRC_PATH/app/viewport.cpp \
    $$OPERAT_SRC_PATH/common/grid_metrics.cpp \
    $$OPERAT_SRC_PATH/common/style.cpp \
    $$OPERAT_SRC_PATH/components/button.cpp \
    $$OPERAT_SRC_PATH/components/camera.cpp \
    $$OPERAT_SRC_PATH/components/camera_control.cpp \
    $$OPERAT_SRC_PATH/components/component.cpp \
    $$OPERAT_SRC_PATH/components/display.cpp \
    $$OPERAT_SRC_PATH/components/grid.cpp \
    $$OPERAT_SRC_PATH/components/label.cpp \
    $$OPERAT_SRC_PATH/components/line.cpp \
    $$OPERAT_SRC_PATH/components/menu.cpp \
    $$OPERAT_SRC_PATH/components/persone.cpp \
    $$OPERAT_SRC_PATH/components/scene.cpp \
    $$OPERAT_SRC_PATH/components/scene_manager.cpp \
    $$OPERAT_SRC_PATH/components/shape.cpp \
    $$OPERAT_SRC_PATH/components/sprite.cpp \
    $$OPERAT_SRC_PATH/components/updater.cpp \
    $$OPERAT_SRC_PATH/components/vehicle_control.cpp \
    $$OPERAT_SRC_PATH/events/event.cpp \
    $$OPERAT_SRC_PATH/events/event_condition.cpp \
    $$OPERAT_SRC_PATH/events/event_listener.cpp \
    $$OPERAT_SRC_PATH/events/event_watcher.cpp \
    $$OPERAT_SRC_PATH/events/input_event.cpp \
    $$OPERAT_SRC_PATH/events/invoke_event.cpp \
    $$OPERAT_SRC_PATH/events/key_event.cpp \
    $$OPERAT_SRC_PATH/events/mouse_event.cpp \
    $$OPERAT_SRC_PATH/events/wheel_event.cpp \

HEADERS += \
    $$OPERAT_SRC_PATH/app/engine.h \
    $$OPERAT_SRC_PATH/app/menu_stage.h \
    $$OPERAT_SRC_PATH/app/message_service.h \
    $$OPERAT_SRC_PATH/app/resource_manager.h \
    $$OPERAT_SRC_PATH/app/service.h \
    $$OPERAT_SRC_PATH/app/service_manager.h \
    $$OPERAT_SRC_PATH/app/stage.h \
    $$OPERAT_SRC_PATH/app/stage_manager.h \
    $$OPERAT_SRC_PATH/app/store_service.h \
    $$OPERAT_SRC_PATH/app/viewport.h \
    $$OPERAT_SRC_PATH/common/config.h \
    $$OPERAT_SRC_PATH/common/debug.h \
    $$OPERAT_SRC_PATH/common/default_value.h \
    $$OPERAT_SRC_PATH/common/geometry_math.h \
    $$OPERAT_SRC_PATH/common/grid_metrics.h \
    $$OPERAT_SRC_PATH/common/simple_function.h \
    $$OPERAT_SRC_PATH/common/straight.h \
    $$OPERAT_SRC_PATH/common/style.h \
    $$OPERAT_SRC_PATH/common/utils.h \
    $$OPERAT_SRC_PATH/components/button.h \
    $$OPERAT_SRC_PATH/components/camera.h \
    $$OPERAT_SRC_PATH/components/camera_control.h \
    $$OPERAT_SRC_PATH/components/component.h \
    $$OPERAT_SRC_PATH/components/display.h \
    $$OPERAT_SRC_PATH/components/grid.h \
    $$OPERAT_SRC_PATH/components/label.h \
    $$OPERAT_SRC_PATH/components/line.h \
    $$OPERAT_SRC_PATH/components/menu.h \
    $$OPERAT_SRC_PATH/components/persone.h \
    $$OPERAT_SRC_PATH/components/scene.h \
    $$OPERAT_SRC_PATH/components/scene_manager.h \
    $$OPERAT_SRC_PATH/components/shape.h \
    $$OPERAT_SRC_PATH/components/sprite.h \
    $$OPERAT_SRC_PATH/components/updater.h \
    $$OPERAT_SRC_PATH/components/vehicle_control.h \
    $$OPERAT_SRC_PATH/events/event.h \
    $$OPERAT_SRC_PATH/events/event_condition.h \
    $$OPERAT_SRC_PATH/events/event_listener.h \
    $$OPERAT_SRC_PATH/events/event_watcher.h \
    $$OPERAT_SRC_PATH/events/input_event.h \
    $$OPERAT_SRC_PATH/events/invoke_event.h \
    $$OPERAT_SRC_PATH/events/key_event.h \
    $$OPERAT_SRC_PATH/events/mouse_event.h \
    $$OPERAT_SRC_PATH/events/wheel_event.h \

RESOURCES += \
    $$OPERAT_SRC_PATH/resources/resources.qrc


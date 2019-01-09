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
    component.cpp \
    resource_manager.cpp \
    level.cpp \
    stage.cpp \
    stage_manager.cpp \
    main_menu_stage.cpp \
    events/wheel_event.cpp \
    events/mouse_event.cpp \
    events/key_event.cpp \
    events/invoke_event.cpp \
    events/event.cpp \
    common/grid_metrics.cpp \
    common/style.cpp \
    preview/preview.cpp \
    preview/preview_stage.cpp \
    components/camera.cpp \
    components/grid.cpp \
    components/label.cpp \
    preview/main.cpp \
    components/persone.cpp \
    components/scene.cpp \
    components/shape.cpp \
    components/sprite.cpp \
    events/event_listener.cpp \
    components/button.cpp \
    viewport.cpp \
    components/camera_control.cpp

HEADERS += \
    component.h \
    resource_manager.h \
    level.h \
    stage.h \
    stage_manager.h \
    main_menu_stage.h \
    events/wheel_event.h \
    events/invoke_event.h \
    events/key_event.h \
    events/event.h \
    events/mouse_event.h \
    common/utils.h \
    common/style.h \
    common/button_function.h \
    common/config.h \
    common/debug.h \
    common/default_value.h \
    common/grid_metrics.h \
    preview/preview.h \
    preview/preview_stage.h \
    components/camera.h \
    components/grid.h \
    components/persone.h \
    components/scene.h \
    components/shape.h \
    components/sprite.h \
    components/label.h \
    events/event_listener.h \
    components/button.h \
    viewport.h \
    components/camera_control.h

RESOURCES += \
    resources.qrc

DISTFILES += \
    resources.json

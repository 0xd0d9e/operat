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
        main.cpp \
    component.cpp \
    shape.cpp \
    scene.cpp \
    viewport.cpp \
    preview.cpp \
    viewport_listener.cpp \
    viewport_control.cpp \
    viewport_mouse_event.cpp \
    grid.cpp \
    persone.cpp \
    camera.cpp \
    label.cpp \
    sprite.cpp \
    resource_manager.cpp \
    event.cpp \
    grid_metrics.cpp \
    level.cpp \
    stage.cpp \
    stage_manager.cpp \
    menu_button.cpp \
    main_menu_stage.cpp \
    style.cpp \
    preview_stage.cpp

HEADERS += \
    component.h \
    shape.h \
    scene.h \
    viewport.h \
    preview.h \
    viewport_listener.h \
    viewport_control.h \
    viewport_mouse_event.h \
    grid.h \
    persone.h \
    config.h \
    debug.h \
    camera.h \
    utils.h \
    label.h \
    sprite.h \
    resource_manager.h \
    event.h \
    grid_metrics.h \
    level.h \
    stage.h \
    stage_manager.h \
    menu_button.h \
    main_menu_stage.h \
    style.h \
    button_function.h \
    default_value.h \
    preview_stage.h

RESOURCES += \
    resources.qrc

DISTFILES += \
    resources.json

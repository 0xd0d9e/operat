#include "app.h"

#include "common/style.h"
#include "common/utils.h"
#include "components/shape.h"
#include "menu_stage.h"
#include "preview/preview_stage.h"
#include "resource_manager.h"
#include "service_manager.h"

#include <QApplication>

App::App()
    : stageManager(&viewport)
{
    initResources();

    MenuStage* mainMenuStage = new MenuStage();
    PreviewStage* previewStage = new PreviewStage([this](){stageManager.setCurrentStage("MainMenu");});

    stageManager.addStage("MainMenu", mainMenuStage);
    stageManager.addStage("Preview", previewStage);

    mainMenuStage->addButton(tr("Preview"), [this](){stageManager.setCurrentStage("Preview");});
    mainMenuStage->addButton(tr("Exit"), [](){qApp->quit();});

    stageManager.setCurrentStage("MainMenu");
}

void App::start()
{
    viewport.show();
    viewport.resize(800, 600);
}

void App::initResources()
{
    auto resourceManager = ServiceManager::ask<ResourceManager>();
    resourceManager->addImage("WorldMap", QImage(":/assets/images/SimpleWMAuthaGraph.png"));
    resourceManager->addImage("Ship", QImage(":/assets/images/ship.png"));
    resourceManager->setPreset("persone-hand", {{"type", Shape::Ellipse},
                                                {"style", Style(QPen(Qt::black, 0), QBrush("#ffaaaa"))},
                                                {"rect", makeRect(0.25, 0.25)}});
    resourceManager->setPreset("persone-body", {{"type", Shape::Ellipse},
                                                {"style", Style(QPen(Qt::black, 0), QBrush("#229922"))},
                                                {"rect", makeRect(0.8, 0.8)}});
    resourceManager->setPreset("menuButton", {{"type", Shape::Rectangle},
                                              {"color", QColor(Qt::black)},
                                              {"font", QFont("Monospace", 16)},
                                              {"margin", 5.0},
                                              {"textAlign", Qt::AlignCenter},
                                              {"minimumWidth", 200},
                                              {"normalStyle", Style(QPen(Qt::black, 2), QBrush("#aaffaa"))},
                                              {"pressedStyle", Style(QPen(Qt::black, 2), QBrush("#88aa88"))},
                                              {"highlightStyle", Style(QPen(Qt::yellow, 2), QBrush("#55ff55"))}});
}

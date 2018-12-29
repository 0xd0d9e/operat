#include "preview.h"

#include "main_menu_stage.h"
#include "preview_stage.h"
#include "resource_manager.h"
#include "shape.h"
#include "style.h"
#include "utils.h"

#include <QApplication>

Preview::Preview()
    : stageManager(&viewport)
{
    initResources();

    MainMenuStage* mainMenuStage = new MainMenuStage();
    PreviewStage* previewStage = new PreviewStage();

    stageManager.addStage("MainMenu", mainMenuStage);
    stageManager.addStage("Preview", previewStage);

    mainMenuStage->addButton(tr("Preview"), [this](){stageManager.setCurrentStage("Preview");});
    mainMenuStage->addButton(tr("Exit"), [](){qApp->quit();});

    stageManager.setCurrentStage("MainMenu");
}

void Preview::start()
{
    viewport.show();
    viewport.resize(800, 600);
}

void Preview::initResources()
{
    auto& resourceManager = ResourceManager::instance();
    resourceManager.addImage("WorldMap", QImage(":/assets/images/world_map.jpg"));
    resourceManager.setPreset("persone-hand", {{"type", Shape::Ellipse},
                                               {"style", Style(QPen(Qt::black, 0), QBrush("#ffaaaa"))},
                                               {"rect", makeRect(0.25, 0.25)}});
    resourceManager.setPreset("persone-body", {{"type", Shape::Ellipse},
                                               {"style", Style(QPen(Qt::black, 0), QBrush("#229922"))},
                                               {"rect", makeRect(0.8, 0.8)}});
    resourceManager.setPreset("menuButton", {{"type", Shape::Rectangle},
                                             {"color", QColor(Qt::black)},
                                             {"font", QFont("Monospace", 16)},
                                             {"margin", 5.0},
                                             {"textAlign", Qt::AlignCenter},
                                             {"minimumWidth", 200},
                                             {"normalStyle", Style(QPen(Qt::black, 2), QBrush("#aaffaa"))},
                                             {"pressedStyle", Style(QPen(Qt::black, 2), QBrush("#88aa88"))},
                                             {"highlightStyle", Style(QPen(Qt::yellow, 2), QBrush("#55ff55"))}});
}

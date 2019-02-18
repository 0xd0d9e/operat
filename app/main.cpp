#include "engine.h"

#include "menu_stage.h"

#include <preview/preview_stage.h>
#include <grids/grids.h>
#include <ecdis/ecdis_stage.h>

#include <QApplication>
#include <QVariant>




int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    Engine engine;

    PreviewStage* previewStage = new PreviewStage();
    app.connect(previewStage, &PreviewStage::escape, &engine, [&engine](){engine.setCurrentStage("MainMenu");});

    MenuStage* mainMenuStage = new MenuStage();
    mainMenuStage->addButton(app.tr("Ecdis"), [&engine](){engine.setCurrentStage("Ecdis");});
    mainMenuStage->addButton(app.tr("Preview"), [&engine](){engine.setCurrentStage("Preview");});
    mainMenuStage->addButton(app.tr("Grids"), [&engine](){engine.setCurrentStage("Grids");});
    mainMenuStage->addButton(app.tr("Exit"), [](){qApp->quit();});

    EcdisStage* ecdisStage = new EcdisStage();
    GridsStage* gridsStage = new GridsStage();

    engine.addStage("MainMenu", mainMenuStage);
    engine.addStage("Ecdis", ecdisStage);
    engine.addStage("Preview", previewStage);
    engine.addStage("Grids", gridsStage);
    engine.setCurrentStage("MainMenu");
    engine.start();

    return app.exec();
}

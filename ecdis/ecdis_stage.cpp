#include "ecdis_stage.h"

EcdisStage::EcdisStage()
{
    sceneManager.setScene(&routeMonitorScene);
}

void EcdisStage::setViewport(Viewport* viewport)
{
    sceneManager.setViewport(viewport);
}

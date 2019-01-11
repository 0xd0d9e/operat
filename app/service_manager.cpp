#include "service_manager.h"

ServiceManager& ServiceManager::instance()
{
    static ServiceManager serviceManager;
    return serviceManager;
}

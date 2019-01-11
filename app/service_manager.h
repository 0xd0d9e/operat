#pragma once

#include <memory>

#include <QHash>

class Service;

using ServiceSP = std::shared_ptr<Service>;

class ServiceManager
{
public:
    template <class Type>
    static void createService()
    {
        ServiceManager::instance().services[typeid(Type).name()].reset(new Type());
    }

    template <class Type>
    static std::shared_ptr<Type> get()
    {
        const QString name = typeid(Type).name();
        return std::dynamic_pointer_cast<Type>(ServiceManager::instance().services.value(name));
    }

    template <class Type>
    static std::shared_ptr<Type> ask()
    {
        auto& manager = ServiceManager::instance();
        const QString name = typeid(Type).name();
        auto iter = manager.services.find(name);
        std::shared_ptr<Type> service;
        if (iter == manager.services.end())
        {
            service.reset(new Type());
            manager.services[name] = service;
        }
        else
        {
            service = std::dynamic_pointer_cast<Type>(*iter);
        }
        return service;
    }

    static ServiceManager& instance();

private:
    ServiceManager() = default;
    ServiceManager(const ServiceManager &) = default;
    ServiceManager & operator = (const ServiceManager &) = default;

    QHash<QString,ServiceSP> services;
};


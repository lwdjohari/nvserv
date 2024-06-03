#pragma once

#include <memory>
#include "nvserv/global_macro.h"

NVREST_BEGIN_NAMESPACE(components)


class ServiceManager;
using ServiceManagerPtr = std::shared_ptr<ServiceManager>;


class ServiceManager
{
private:
    
public:
    ServiceManager();
    ~ServiceManager();
};

class ServiceComponentBase{

};


template <typename TComponent>
class Service{

};



NVREST_END_NAMESPACE
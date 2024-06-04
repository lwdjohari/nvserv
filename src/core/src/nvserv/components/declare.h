#pragma once

#include <ostream>

#include "nvm/macro.h"
#include "nvserv/global_macro.h"

NVREST_BEGIN_NAMESPACE(components)

class ComponentLocator;
class ComponentConfig;
class ComponentBase;
class Component;

enum class ComponentType {
  kInknown = 0,
  kServerRest = 1,
  kServerGrpc = 2,
  kServerSocket = 3,
  kCustomDefined = 4,
  kPostgresFeature = 5,
  kOracleFeature = 6,
  kHandlerJson = 7,
  kHandlerBasic = 8,
  kHandlerGrpc = 9,
  kHandlerTcpSocket = 10,
  kHandlerUdpSocket = 11
};

NVM_ENUM_CLASS_DISPLAY_TRAIT(ComponentType)

NVREST_END_NAMESPACE

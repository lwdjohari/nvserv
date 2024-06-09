#pragma once

#include "nvserv/components/component.h"
#include "nvserv/components/component_base.h"
#include "nvserv/components/component_config.h"
#include "nvserv/components/component_list_base.h"
#include "nvserv/components/component_locator.h"
#include "nvserv/components/declare.h"
NVREST_BEGIN_NAMESPACE(components)

/// @brief Custom Component (non-core must be inherited from Component)
class Component : public ComponentBase {
 public:
  explicit Component(const components::ComponentLocator& locator,
                     const components::ComponentConfig& config,
                     ComponentType type)
                  : ComponentBase(locator, config, type, true) {}
  virtual ~Component() {}
};

NVREST_END_NAMESPACE

#pragma once
#include "nvserv/components/component.h"

namespace hello_world {
class UtilComponent : public nvserv::components::Component {
 private:
 public:
  UtilComponent(const nvserv::components::ComponentLocator& locator,
                const nvserv::components::ComponentConfig& config,
                nvserv::components::ComponentType type)
                  : nvserv::components::Component(locator, config, type) {};
  ~UtilComponent() {};
};

}  // namespace hello_world

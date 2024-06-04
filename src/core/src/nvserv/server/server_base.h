#pragma once

#include <memory>
#include <cstdint>
#include <string>

#include "nvserv/components/component.h"
#include "nvserv/global_macro.h"

NVREST_BEGIN_NAMESPACE(server)

class ServerBase : public components::ComponentBase {
 public:
  virtual ~ServerBase(){};

  virtual void Start() = 0;

  virtual void Stop() = 0;

  virtual void Wait() = 0;

  virtual bool IsRun() const = 0;

 protected:
  ServerBase(components::ComponentLocator& locator,
             components::ComponentConfig& config,
             nvserv::components::ComponentType type)
                  : components::ComponentBase(locator, config, type) {}
};

NVREST_END_NAMESPACE
#pragma once

#include <chrono>
#include <ostream>

#include "nvserv/components/component_base.h"
#include "nvserv/global_macro.h"
#include "nvserv/storages/cluster_config.h"
#include "nvserv/storages/declare.h"
NVREST_BEGIN_NAMESPACE(storages)

class StorageServer : public components::ComponentBase {
 public:
  StorageServer(const components::ComponentLocator& locator,
                const components::ComponentConfig& config,
                components::ComponentType type, bool is_monitor)
                  : components::ComponentBase(locator, config, type,
                                              is_monitor) {}

  virtual ~StorageServer(){};

  virtual const ClusterConfigList& ClusterConfigs() const = 0;

  virtual bool TryConnect() = 0;

  virtual bool Shutdown(
      bool grace_shutdown = true,
      std::chrono::seconds deadline = std::chrono::seconds(0)) = 0;

  virtual TransactionPtr Begin() = 0;

  virtual const ServerPoolPtr Pool() const = 0;

  virtual StorageInfo GetStorageServerInfo() const = 0;
};

NVREST_END_NAMESPACE
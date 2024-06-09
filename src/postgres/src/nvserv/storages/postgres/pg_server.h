#pragma once

#include "nvserv/storages/postgres/declare.h"
#include "nvserv/storages/postgres/pg_cluster_config.h"
#include "nvserv/storages/postgres/pg_connection.h"
#include "nvserv/storages/postgres/pg_transaction.h"
#include "nvserv/storages/storage_server.h"

NVREST_BEGIN_NAMESPACE(storages::postgres)

class PgServer final : public StorageServer {
 public:
  explicit PgServer(const components::ComponentLocator& locator,
                    const components::ComponentConfig& config)
                  : StorageServer(locator, config,
                                  components::ComponentType::kPostgresFeature),
                    configs_(storages::StorageType::Postgres) {}
  ~PgServer() {}

  bool TryConnect() override {
    return false;
  }

  bool Shutdown(
      bool grace_shutdown = true,
      std::chrono::seconds deadline = std::chrono::seconds(0)) override {
    return false;
  }

  TransactionPtr Begin() override {
    return __NR_RETURN_MOVE(std::make_shared<PgTransaction>(this));
  }

  const ClusterConfigList& ClusterConfigs() const override {
    return configs_;
  }
  const ServerPoolPtr Pool() const override {
    return nullptr;
  }

  StorageInfo GetStorageServerInfo() const override {
    return StorageInfo();
  }

 private:
  ClusterConfigList configs_;
};

NVREST_END_NAMESPACE
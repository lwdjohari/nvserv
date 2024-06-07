
#pragma once

#include <nvm/macro.h>

#include <ostream>
#include <vector>

#include "nvserv/global_macro.h"

NVREST_BEGIN_NAMESPACE(storages)

class StorageServer;
class Transaction;
class ServerPool;
class ClusterConfig;
class ExecutionResult;
class RowResult;

namespace postgres{
    class PgServer;
}

using StorageServerPtr = std::shared_ptr<StorageServer>;
using TransactionPtr = std::shared_ptr<Transaction>;
using ServerPoolPtr = std::shared_ptr<ServerPool>;
using ClusterConfigListType = std::vector<ClusterConfig>;
using ExecutionResultPtr = std::shared_ptr<ExecutionResult>;
using RowResultPtr = std::shared_ptr<RowResult>;

/// @brief NvServ storage driver
enum class StorageType {
  Unknown = 0,   // Storage driver is uninitialized
  Postgres = 1,  // Postgres Database Server
  Oracle = 2,    // Oracle Database Server
  Mysql = 3,     // Mysql is not yet supported
  SqlLite = 4,   // Sqlite is not yet supported
  Redis = 5,     // Redis is not yet supported
  Parquet = 6,   // Parquet is not yet supported
  NvXcel = 7     // NvXcel is not yet supported
};

NVM_ENUM_CLASS_DISPLAY_TRAIT(StorageType)

NVM_ENUM_TO_STRING_FORMATTER(StorageType, case StorageType::Unknown
                             // cppcheck-suppress syntaxError
                             : return "Unknown";
                             case StorageType::Postgres
                             : return "Postgres";
                             case StorageType::Oracle
                             : return "Oracle";
                             case StorageType::Mysql
                             : return "Mysql";
                             case StorageType::SqlLite
                             : return "SqlLite";
                             case StorageType::Redis
                             : return "Redis";
                             case StorageType::Parquet
                             : return "Parquet";
                             case StorageType::NvXcel
                             : return "NvXcel";)

class StorageInfo {
 public:
  StorageInfo()
                  : name_(),
                    version_(),
                    info_(),
                    type_(),
                    is_trans_supported_() {}

  ~StorageInfo();

  virtual const __NR_STRING_COMPAT_REF Name() const {
    return name_;
  };

  virtual const __NR_STRING_COMPAT_REF Version() const {
    return version_;
  };

  virtual const __NR_STRING_COMPAT_REF Info() const {
    return info_;
  };

  virtual bool TransactionSupported() const {
    return is_trans_supported_;
  };

  virtual StorageType Type() const {
    return type_;
  };

  virtual std::string GetServerInfo() {
    return "Unimplemented";
  };

 protected:
  std::string name_;
  std::string version_;
  std::string info_;
  StorageType type_;
  bool is_trans_supported_;
};

NVREST_END_NAMESPACE
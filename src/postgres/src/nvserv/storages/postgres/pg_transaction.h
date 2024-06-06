#pragma once

#include <iostream>

#include "nvserv/global_macro.h"
#include "nvserv/storages/postgres/declare.h"
#include "nvserv/storages/transaction.h"

NVREST_BEGIN_NAMESPACE(storages::postgres)

class PgTransaction : public Transaction {
 public:
  PgTransaction() : Transaction() {}
  virtual ~PgTransaction() {}

  void Commit() override {}
  void Rollback() override {}

 protected:
  void ExecuteImpl(const __NR_STRING_COMPAT_REF query,
                   const std::vector<std::any>& args) override {
    std::cout << "Executing query: " << query << std::endl;
    for (const auto& arg : args) {
      // Handle each argument based on its type
      if (arg.type() == typeid(int)) {
        std::cout << "int: " << std::any_cast<int>(arg) << std::endl;
      } else if (arg.type() == typeid(std::string)) {
        std::cout << "string: " << std::any_cast<std::string>(arg) << std::endl;
      } else {
        std::cout << "Unknown type" << std::endl;
      }
    }
  }
};

NVREST_END_NAMESPACE
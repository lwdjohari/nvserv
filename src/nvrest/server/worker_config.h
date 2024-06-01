#pragma once
#include <cstdint>
#include <string>

#include "nvm/macro.h"

namespace nvm::nvrest::server {
enum class WorkerType { IoWorker, FrameworkWorker };

class WorkerConfig {
 private:
  std::string name_;
  uint16_t worker_num_;
  WorkerType worker_type_;

 public:
  WorkerConfig(const std::string& worker_name, WorkerType type,
               uint16_t worker_num)
                  : name_(std::string(worker_name)),
                    worker_num_(worker_num),
                    worker_type_(type)
                    {};

  const std::string &Name() const{
    return name_;
  }

  WorkerType Type() const{
    return worker_type_;
  } 

  const uint16_t& WorkerNumber() const{
    return worker_num_;
  }

};

}  // namespace nvm::nvrest::server
#pragma once

#include "nvserv/global_macro.h"
#include "grpcpp/grpcpp.h"
#include "nvserv/components/component_locator.h"
#include "nvserv/components/component_config.h"

NVREST_BEGIN_NAMESPACE(handlers)

class GrpcServiceHandlerBase {
 public:
  GrpcServiceHandlerBase(const components::ComponentLocator& locator,
                         const components::ComponentConfig& config,
                         bool is_monitor = false)
      : locator_(locator), config_(config), is_monitor_(is_monitor) {}

  virtual ~GrpcServiceHandlerBase() = default;

 protected:
  virtual void HandleRequest(grpc::ServerContext* context,
                             const grpc::ByteBuffer* request,
                             grpc::ByteBuffer* response) const = 0;

  const components::ComponentLocator& GetLocator() const { return locator_; }
  const components::ComponentConfig& GetConfig() const { return config_; }
  bool IsMonitor() const { return is_monitor_; }

 private:
  const components::ComponentLocator& locator_;
  const components::ComponentConfig& config_;
  bool is_monitor_;
};

NVREST_END_NAMESPACE
#pragma once
#include <memory>
#include <unordered_map>
#include <absl/container/node_hash_map.h>

#include "nvserv/components/component_base.h"
#include "nvserv/components/component_config.h"
#include "nvserv/components/component_locator.h"
#include "nvserv/global_macro.h"
#if NVSERV_SERVER_GRPC == 1
#include "nvserv/handlers/grpc_service_handler.h"
#endif

#if NVSERV_SERVER_REST == 1
#include "nvserv/handlers/http_basic_handler.h"
#include "nvserv/handlers/http_json_handler.h"
#endif

#include "nvserv/server/grpc_server.h"

NVREST_BEGIN_NAMESPACE(components)

class ComponentList final {
 public:
  using ComponentHolderPtr = std::shared_ptr<ComponentHolder>;
  using ComponentHolderMap =
      absl::node_hash_map<std::string, ComponentHolderPtr>;

  ComponentList();

  template <typename TComponent>
  ComponentList& RegisterComponent();

#if NVSERV_SERVER_REST == 1
  template <typename TComponent>
  ComponentList& RegisterHttpHandler(bool auth = false);

  template <typename TComponent>
  ComponentList& RegisterHttpHandler(const std::string& endpoint,
                                     bool auth = false);
#endif

#if NVSERV_SERVER_GRPC == 1
  template <typename TComponent>
  ComponentList& RegisterGrpcServiceHandler(bool auth = false);

  template <typename TComponent>
  ComponentList& RegisterGrpcServiceHandler(const std::string& endpoint,
                                     bool auth = false);

#endif

#if NVSERV_SERVER_SOCKET == 1

  template <typename TComponent>
  ComponentList& RegisterTcpHandler();

  template <typename TComponent>
  ComponentList& RegisterUdpHandler();
#endif

  template <typename TComponent>
  ComponentList& RegisterComponent(const std::string& config_name,
                                   bool auth = false);

  ComponentList& SetupServer(const std::string& server_name, ServerType type);
  ComponentList& SetupServer(const std::string& server_name, ServerType type,
                             uint32_t port);
  ComponentList& SetupServer(const std::string& server_name, ServerType type,
                             const std::string& host, uint32_t port);

 private:
  ComponentHolderMap components_;
  std::shared_ptr<components::ComponentLocator> locator_;
  std::shared_ptr<components::ComponentConfig> config_;
};

template <typename TComponent>
ComponentList& ComponentList::RegisterComponent() {
  return *this;
}

#if NVSERV_SERVER_REST == 1
template <typename TComponent>
ComponentList& ComponentList::RegisterHttpHandler(bool auth) {
  return *this;
}

template <typename TComponent>
ComponentList& ComponentList::RegisterHttpHandler(const std::string& endpoint,
                                                  bool auth) {
  return *this;
}

#endif

#if NVSERV_SERVER_GRPC == 1

template <typename TComponent>
ComponentList& ComponentList::RegisterGrpcServiceHandler(bool auth) {
  return *this;
}

template <typename TComponent>
ComponentList& ComponentList::RegisterGrpcServiceHandler(const std::string& endpoint,
                                                  bool auth) {
  return *this;
}

#endif

template <typename TComponent>
ComponentList& ComponentList::RegisterComponent(const std::string& config_name,
                                                bool auth) {
  return *this;
}

NVREST_END_NAMESPACE

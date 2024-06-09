#pragma once
#include <absl/container/node_hash_map.h>
#include <nvm/macro.h>

#include <memory>
#include <unordered_map>

#include "nvserv/components/component.h"
#include "nvserv/components/component_list_base.h"
#include "nvserv/global_macro.h"
#include "nvserv/logs/log.h"
#if NVSERV_SERVER_GRPC == 1
#include "nvserv/handlers/grpc_service_handler.h"
#include "nvserv/server/grpc_server.h"
#endif

#if NVSERV_SERVER_REST == 1
#include "nvserv/handlers/http_basic_handler.h"
#include "nvserv/handlers/http_json_handler.h"
#endif

NVREST_BEGIN_NAMESPACE(components)

class LoggerComponentRegistration {
 public:
  LoggerComponentRegistration(logs::Logging& log, ComponentList& components)
                  : log_(log), components_(components){};

  LoggerComponentRegistration& Initialize(const std::string& log_name) {
    log_.Initialize(log_name);
    return *this;
  }

  LoggerComponentRegistration& AddDefaultConsoleLogger(logs::LogLevel level) {
    log_.AddDefaultConsoleLogger(level);
    return *this;
  }

  LoggerComponentRegistration& AddFileLogger(logs::LogLevel level,
                                             const std::string& filename) {
    log_.AddFileLogger(level, filename);
    return *this;
  };

  ComponentList& RegisterAll(bool set_global_level = false,
                             logs::LogLevel level = logs::LogLevel::Trace) {
    log_.RegisterAll(set_global_level, level);
    return components_;
  }

 private:
  logs::Logging& log_;
  ComponentList& components_;
};

class ComponentList final : public ComponentListBase {
 public:
  ComponentList(ComponentLocator& resolver, ComponentConfig& config);
  virtual ~ComponentList();

  ComponentList(const ComponentListBase&) = delete;
  ComponentList& operator=(const ComponentListBase&) = delete;

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

  LoggerComponentRegistration& RegisterLogger(const std::string& name);

 private:
  std::shared_ptr<LoggerComponentRegistration> logger_register_;
  void CleanUpRegistrant();
};

template <typename TComponent>
ComponentList& ComponentList::RegisterComponent() {
  CleanUpRegistrant();
  return *this;
}

#if NVSERV_SERVER_REST == 1
template <typename TComponent>
ComponentList& ComponentList::RegisterHttpHandler(bool auth) {
  CleanUpRegistrant();
  return *this;
}

template <typename TComponent>
ComponentList& ComponentList::RegisterHttpHandler(const std::string& endpoint,
                                                  bool auth) {
  CleanUpRegistrant();
  return *this;
}

#endif

#if NVSERV_SERVER_GRPC == 1

template <typename TComponent>
ComponentList& ComponentList::RegisterGrpcServiceHandler(bool auth) {
  CleanUpRegistrant();
  return *this;
}

template <typename TComponent>
ComponentList& ComponentList::RegisterGrpcServiceHandler(
    const std::string& endpoint, bool auth) {
  CleanUpRegistrant();

  return *this;
}

#endif

template <typename TComponent>
ComponentList& ComponentList::RegisterComponent(const std::string& config_name,
                                                bool auth) {
  CleanUpRegistrant();

  return *this;
}

NVREST_END_NAMESPACE

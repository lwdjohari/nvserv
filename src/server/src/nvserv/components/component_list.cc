#include "nvserv/components/component_list.h"

#include "component_list.h"

// cppcheck-suppress unknownMacro
NVSERV_BEGIN_NAMESPACE(components)

ComponentList::ComponentList(ComponentLocator& resolver,
                             ComponentConfig& config)
                : ComponentListBase(resolver, config) {}

ComponentList::~ComponentList() {}

ComponentList& ComponentList::SetupServer(const std::string& server_name,
                                          ServerType type) {
  return SetupServer(server_name, type, std::string(), 0);
}

ComponentList& ComponentList::SetupServer(const std::string& server_name,
                                          ServerType type, uint32_t port) {
  return SetupServer(server_name, type, std::string(), port);
}

ComponentList& ComponentList::SetupServer(const std::string& server_name,
                                          ServerType type,
                                          const std::string& host,
                                          uint32_t port) {
  CleanUpRegistrant();

  if (port == 0)
    port = 9001;

#if NVSERV_SERVER_GRPC == 1
  if (type == ServerType::Grpc) {
    RegisterComponentImpl(
        server_name,
        std::make_shared<ComponentHolder>(
            std::string(server_name),
            std::move(server::GrpcServer(resolver_, config_resolver_)), false,
            std::move(std::string(server_name))));

    // components_.emplace(std::string(server_name),
    //                     std::make_shared<ComponentHolder>(
    //                         std::string(server_name),
    //                         std::move(server::GrpcServer(*locator_,
    //                         *config_)), false,
    //                         std::move(std::string(server_name))));

    return *this;
  }
#else
  throw std::runtime_error(
      "Can't create GRPC Server if set(NVSERV_SERVER_GRPC ON) is not set in "
      "CMake or NVSERV_SERVER_GRPC=1 from compile definition is not defined!");
#endif

  return *this;
}

LoggerComponentRegistration& ComponentList::RegisterLogger(
    const std::string& name) {
  CleanUpRegistrant();

  RegisterComponentImpl(
      "logging-component",
      std::make_shared<ComponentHolder>(
          "logging-component",
          std::move(logs::Logging(resolver_, config_resolver_)), false,
          "server::logging"));

  auto logs = std::dynamic_pointer_cast<logs::Logging>(
      GetComponent("logging-component"));

  logs->Initialize(name);
  logger_register_ =
      std::make_shared<LoggerComponentRegistration>(*logs, *this);
  return *logger_register_;
}

void ComponentList::CleanUpRegistrant() {
  if (logger_register_)
    logger_register_ = nullptr;
}

ComponentListBasePtr ComponentLocator::InitializeImpl(
    ComponentLocator& resolver, ComponentConfig& configs) {
  return std::make_shared<ComponentList>(resolver, configs);
}

NVSERV_END_NAMESPACE

NVSERV_BEGIN_NAMESPACE(storages)
namespace postgres {
PgServerPtr PgServer::MakePgServer(
    const std::string& name, std::initializer_list<PgClusterConfig> clusters,
    uint16_t pool_min_worker, u_int16_t pool_max_worker) {
  return nullptr;
};

}  // namespace postgres
NVSERV_END_NAMESPACE

#include "nvserv/components/component_list.h"

// cppcheck-suppress unknownMacro
NVREST_BEGIN_NAMESPACE(components)

ComponentList::ComponentList() : components_() {}

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
  if (port == 0)
    port = 9001;

#if NVSERV_SERVER_GRPC == 1
  if (type == ServerType::Grpc) {
    components_.emplace(std::string(server_name),
                        std::make_shared<ComponentHolder>(
                            std::move(server::GrpcServer(*locator_, *config_)),
                            false, std::move(std::string(server_name))));

    return *this;
  }
#else
  throw std::runtime_error(
      "Can't create GRPC Server if set(NVSERV_SERVER_GRPC ON) is not set in "
      "CMake or NVSERV_SERVER_GRPC=1 from compile definition is not defined!");
#endif

  return *this;
}

NVREST_END_NAMESPACE

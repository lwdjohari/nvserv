#pragma once
#include "nvserv/components/component_config.h"
#include "nvserv/components/component_locator.h"
#include "nvserv/components/declare.h"
#include "nvserv/declare.h"

// cppcheck-suppress unknownMacro
NVREST_BEGIN_NAMESPACE(components)

namespace details {
#if __NR_CPP17
template <class T>
auto GetComponentName() -> decltype(std::string_view{T::ComponentName}) {
  return std::string_view{T::ComponentName};
};
#else
template <class T>
auto GetComponentName() -> decltype(std::string{T::ComponentName}) {
  return std::string{T::ComponentName};
};
#endif

class ComponentHolderBase {
 public:
  ComponentHolderBase() = delete;
  ComponentHolderBase(const ComponentHolderBase&) = delete;
  ComponentHolderBase(ComponentHolderBase&&) = delete;
  ComponentHolderBase& operator=(const ComponentHolderBase&) = delete;
  ComponentHolderBase& operator=(ComponentHolderBase&&) = delete;
};
}  // namespace details

class ComponentBase {
 private:
 public:
  explicit ComponentBase(const components::ComponentLocator& locator,
                         const components::ComponentConfig& config,
                         bool is_monitor = false);
  ~ComponentBase();

 protected:
};

class ComponentList final {
 public:
  ComponentList();

  template <typename TComponent>
  ComponentList& RegisterComponent() &;

  template <typename TComponent>
  ComponentList& RegisterHttpHandler(bool auth = false) &;

  template <typename TComponent>
  ComponentList& RegisterHttpHandler(const std::string& endpoint,
                                     bool auth = false) &;

  template <typename TComponent>
  ComponentList& RegisterGrpcHandler(bool auth = false) &;

  template <typename TComponent>
  ComponentList& RegisterGrpcHandler(const std::string& endpoint,
                                     bool auth = false) &;

  template <typename TComponent>
  ComponentList& RegisterTcpHandler() &;

  template <typename TComponent>
  ComponentList& RegisterUdpHandler() &;

  template <typename TComponent>
  ComponentList& RegisterComponent(const std::string& config_name,
                                   bool auth = false) &;

  ComponentList& SetupServer(ServerType type) {
    return *this;
  };

  ComponentList& SetupServer(ServerType type, uint32_t port) {
    return *this;
  };

  ComponentList& SetupServer(ServerType type, const std::string& host,
                             uint32_t port) {
    return *this;
  };
};

template <typename TComponent>
ComponentList& ComponentList::RegisterComponent() & {
  return *this;
};

template <typename TComponent>
ComponentList& ComponentList::RegisterHttpHandler(bool auth) & {
  return *this;
};

template <typename TComponent>
ComponentList& ComponentList::RegisterHttpHandler(const std::string& endpoint,
                                                  bool auth) & {
  return *this;
};

template <typename TComponent>
ComponentList& ComponentList::RegisterGrpcHandler(bool auth) & {
  return *this;
};

template <typename TComponent>
ComponentList& ComponentList::RegisterGrpcHandler(const std::string& endpoint,
                                                  bool auth) & {
  return *this;
};

template <typename TComponent>
ComponentList& ComponentList::RegisterComponent(const std::string& config_name,
                                                bool auth) & {
  return *this;
}

NVREST_END_NAMESPACE

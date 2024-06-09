#pragma once
#include "nvserv/components/declare.h"
#include "nvserv/declare.h"

// cppcheck-suppress unknownMacro
NVREST_BEGIN_NAMESPACE(components)


namespace impl {
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



}  // namespace impl


class ComponentHolder  {
 public:
  explicit ComponentHolder(const std::string& name,
      ComponentBase&& component, bool is_auth = false,
      const std::string& config_section_name = std::string())
                  : components_(std::make_shared<ComponentBase>(
                        std::forward<ComponentBase>(component))),
                    config_section_name_(config_section_name),
                    is_auth_(false) {}

  ComponentHolder() = delete;
  ComponentHolder(const ComponentHolder&) = delete;
  ComponentHolder(ComponentHolder&&) = delete;
  ComponentHolder& operator=(const ComponentHolder&) = delete;
  ComponentHolder& operator=(ComponentHolder&&) = delete;

  const std::string& Name() const{
    return name_;
  }

  ComponentBasePtr Component() const {
    return components_;
  }

  const std::string& ConfigSection() const{
    return config_section_name_;
  }

  bool IsAuth() const{
    return is_auth_;
  }

 private:
  std::string name_;
  ComponentBasePtr components_;
  std::string config_section_name_;
  bool is_auth_;
};

class ComponentBase {
 private:
 public:
  
  virtual ~ComponentBase(){};

  const ComponentType& Type() const {
    return component_type_;
  }

 protected:
  explicit ComponentBase(const components::ComponentLocator& locator,
                         const components::ComponentConfig& config,
                         ComponentType type, bool is_monitor = false);
  ComponentType component_type_;
};

NVREST_END_NAMESPACE

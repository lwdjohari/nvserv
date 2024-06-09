#pragma once
#include <memory>

#include "nvserv/components/component_list_base.h"
#include "nvserv/components/declare.h"
#include "nvserv/global_macro.h"

NVREST_BEGIN_NAMESPACE(components)
class ComponentLocator {
 public:
  explicit ComponentLocator(ComponentConfig& configs)
                  : components_(InitializeImpl(*this, configs)) {}

  virtual ~ComponentLocator() {}

  // void Initialize() {
  //   components_ = std::move(InitializeImpl());
  // };

  ComponentListBasePtr Components() {
    return components_;
  }

  const ComponentListBasePtr Components() const {
    return components_;
  }

  const ComponentBasePtr Resolve(const std::string& name) const {
    if (!components_)
      return nullptr;

    return components_->GetComponent(name);
  }

  ComponentBasePtr Resolve(const std::string& name) {
    if (!components_)
      return nullptr;

    return components_->GetComponent(name);
  }

 private:
  std::shared_ptr<ComponentListBase> components_;

  ComponentListBasePtr InitializeImpl(ComponentLocator& resolver,
                                      ComponentConfig& config);
};
NVREST_END_NAMESPACE

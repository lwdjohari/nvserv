#pragma once

#include <absl/container/node_hash_map.h>

#include <memory>

#include "nvserv/components/component_base.h"
#include "nvserv/components/declare.h"
#include "nvserv/exceptions.h"
#include "nvserv/global_macro.h"
#include "nvserv/headers/absl_thread.h"

NVREST_BEGIN_NAMESPACE(components)
using ComponentHolderPtr = std::shared_ptr<ComponentHolder>;

class ComponentListBase {
 public:
  using ComponentHolderMap =
      absl::node_hash_map<std::string, ComponentHolderPtr>;

  ComponentListBase(ComponentLocator& resolver,
                    ComponentConfig& config_resolver)
                  : resolver_(resolver), config_resolver_(config_resolver) {}

  virtual ~ComponentListBase(){};

  ComponentListBase(const ComponentListBase&) = delete;
  ComponentListBase& operator=(const ComponentListBase&) = delete;

  const ComponentHolderMap& Components() const {
    return components_;
  }

  const ComponentBasePtr GetComponent(const std::string& name) const {
    if (!components_.contains(name))
      throw NullReferenceException("Component \"" + name + "\" not found");

    return components_.at(name)->Component();
  }

   ComponentBasePtr GetComponent(const std::string& name)  {
    if (!components_.contains(name))
      throw NullReferenceException("Component \"" + name + "\" not found");

    return components_.at(name)->Component();
  }

 protected:
  absl::Mutex mutex_;
  ComponentHolderMap components_;
  ComponentLocator& resolver_;
  ComponentConfig& config_resolver_;

  virtual void RegisterComponentImpl(const std::string& name,
                                     ComponentHolderPtr&& component) {
    absl::MutexLock lock(&mutex_);
    if (components_.contains(name)) {
      throw InvalidArgException("Duplicate component name, Component name must "
                                "be unique across NvServ.");
    }

    components_.emplace(std::string(name),
                        std::forward<ComponentHolderPtr>(component));
  }
};

NVREST_END_NAMESPACE
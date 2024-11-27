#pragma once

#include "nvserv/components/component.h"
#include "nvserv/components/component_list.h"
#include "nvserv/global_macro.h"
#include "nvserv/headers/absl_thread.h"

NVSERV_BEGIN_NAMESPACE(server)

class MainExecutionContext;

using MainExecutionContextPtr = std::shared_ptr<MainExecutionContext>;

class MainExecutionContext final {
 public:
  explicit MainExecutionContext(const std::string& name)
                  : configs_(std::make_shared<components::ComponentConfig>()),
                    resolver_(std::make_shared<components::ComponentLocator>(
                        *configs_)),
                    server_component_(nullptr),
                    name_(std::string(name)),
                    type_() {}

  virtual ~MainExecutionContext(){};

  components::ComponentLocatorPtr ComponentResolver() {
    return resolver_;
  }

  components::ComponentPtr ServerComponent() {
    return server_component_;
  };

  components::ComponentListPtr Components() {
    return std::dynamic_pointer_cast<components::ComponentList>(
        resolver_->Components());
  }

  void Start() {}

  void Stop() {}

  void Wait() {}

  bool IsRun() const {
    return false;
  }

  const ServerType& Type() const {
    return type_;
  }

  static void CreateContext(const std::string& name) {
    absl::MutexLock lock(&g_context_mutex_);
    if (MainExecutionContext::g_main_context_)
      throw RuntimeException("Main Execution Context already running, only one "
                             "MainExecutionContext per executable. ");

    MainExecutionContext::g_main_context_ =
        std::make_shared<MainExecutionContext>(name);
  }

  static MainExecutionContext& Context() {
    if (!MainExecutionContext::g_main_context_)
      throw NullReferenceException("Null reference MainExecutionContext, call "
                                   "CreateContext() before calling Context().");

    return *MainExecutionContext::g_main_context_;
  }

 protected:
  components::ComponentConfigPtr configs_;
  components::ComponentLocatorPtr resolver_;
  components::ComponentPtr server_component_;
  std::string name_;
  ServerType type_;

 private:
  static MainExecutionContextPtr g_main_context_;
  static absl::Mutex g_context_mutex_;
};
NVSERV_END_NAMESPACE
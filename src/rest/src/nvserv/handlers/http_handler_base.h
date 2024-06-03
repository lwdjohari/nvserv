#pragma once

#include "nvserv/components/component.h"
#include "nvserv/components/component_base.h"
#include "nvserv/components/component_config.h"
#include "nvserv/components/component_locator.h"
#include "nvserv/global_macro.h"
#include "nvserv/http/http_request.h"
#include "nvserv/http/http_request_context.h"

NVREST_BEGIN_NAMESPACE(handlers)

class HttpHandlerBase : public components::ComponentBase {
 private:
 public:
  HttpHandlerBase(const components::ComponentLocator& locator,
                  const components::ComponentConfig& config,
                  bool is_monitor = false)
                  : ComponentBase(locator, config, is_monitor){};
  ~HttpHandlerBase(){};

 protected:
  virtual void ParseRequestData(const http::HttpRequestContext& context,
                                http::HttpRequest& request) const = 0;
};

NVREST_END_NAMESPACE
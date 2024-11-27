#pragma once

#include "nvserv/components/component.h"
#include "nvserv/global_macro.h"
#include "nvserv/http/http_request.h"
#include "nvserv/http/http_request_context.h"

NVSERV_BEGIN_NAMESPACE(handlers)

class HttpHandlerBase : public components::Component {
 private:
 public:
  HttpHandlerBase(const components::ComponentLocator& locator,
                  const components::ComponentConfig& config,
                  components::ComponentType type
                  )
                  : Component(locator, config,type){};
  ~HttpHandlerBase(){};

 protected:
  virtual void ParseRequestData(const http::HttpRequestContext& context,
                                http::HttpRequest& request) const = 0;
};

NVSERV_END_NAMESPACE
#pragma once

#include "nvserv/global_macro.h"
#include "nvserv/formats/json/value.h"
#include "nvserv/formats/json/value_builder.h"
#include "nvserv/handlers/http_handler_base.h"

NVREST_BEGIN_NAMESPACE(handlers)

class HttpJsonHandlerBase : public HttpHandlerBase {
 public:
  HttpJsonHandlerBase(const components::ComponentLocator& locator,
                      const components::ComponentConfig& config,
                      bool is_monitor = false)
                  : HttpHandlerBase(locator, config, is_monitor) {}

  virtual formats::json::Value HandleJsonRequest(
      const http::HttpRequestContext& context, const http::HttpRequest& request,
      formats::json::Value& json) const = 0;

 protected:
  void ParseRequestData(const http::HttpRequestContext& context,
                        http::HttpRequest& request) const override;

 private:
};

NVREST_END_NAMESPACE
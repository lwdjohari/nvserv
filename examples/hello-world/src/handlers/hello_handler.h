#pragma once

#include <nvserv/handlers/http_json_handler.h>
#include <nvserv/storages/postgres/pg_server.h>

namespace helloworld {
class HelloWorldHandler final : public nvserv::handlers::HttpJsonHandlerBase {
 public:
  HelloWorldHandler(const nvserv::components::ComponentLocator& locator,
                    const nvserv::components::ComponentConfig& config)
                  : nvserv::handlers::HttpJsonHandlerBase(locator, config) {}
 
  nvserv::formats::json::Value HandleJsonRequest(
      const nvserv::http::HttpRequestContext& context,
      const nvserv::http::HttpRequest& request,
      nvserv::formats::json::Value& json) const override {
      nvserv::storages::postgres::PgServer pgserver;
    return nvserv::formats::json::Value();
  }
};
}  // namespace helloworld

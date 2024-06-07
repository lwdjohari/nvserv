#pragma once

#include <nvm/dates/datetime.h>
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
    auto tx = pg_->Begin();
    int32_t status_param = 1;
    auto result =
        tx->Execute("select * from employee where status = $1", status_param);

    if (!result->Empty()) {
      for (auto row : *result) {
        auto emp_id = row->As<int32_t>("emp_id");
        auto emp_name = row->As<std::string>("emp_name");
        auto dept_id = row->As<std::string>("dept_id");
        auto sect_name = row->As<std::string>("sect_name");
        auto status = row->As<int16_t>("status");
        auto dob = row->AsDateTimeOffset<nvm::dates::DateTime>("dob");

        std::cout << "[" << emp_id << "] " << emp_name << " (" << dept_id << ":"
                  << sect_name << ", " << dob << ", " << status << ")"
                  << std::endl;
      }
    }

    // No need for manual tx.Rollback() or tx.Release
    // When TransactionPtr out-of-scope
    // automatically checking what need to do.
    tx->Rollback();

    return nvserv::formats::json::Value();
  }

 private:
  nvserv::storages::postgres::PgServerPtr pg_;
};
}  // namespace helloworld

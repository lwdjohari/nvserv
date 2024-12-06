#pragma once

#include <functional>
#include <stdexcept>
#include <string>
#include <unordered_map>
#include <vector>

#include "nvserv/global_macro.h"
#include "nvserv/handlers/http_handler_base.h"


NVSERV_BEGIN_NAMESPACE(http)
class Request;
class Response;


class Route {
 public:
  using HandlerFn = std::function<void(
      const http::Request& request, const http::Response& response,
      std::shared_ptr<handlers::HandlerBase> handler,
      const std::unordered_map<std::string, std::string>& params)>;

  Route(const size_t key, const std::string& path,
        std::shared_ptr<handlers::HandlerBase> req_handler);
  const size_t& Key() const;
  const std::string& Path() const;
  const std::shared_ptr<handlers::HandlerBase> RequestHandler() const;
  // const HandlerFn& Handler() const;

 private:
  size_t key_;
  std::string path_;
  HandlerFn handler_;
  std::shared_ptr<handlers::HandlerBase> req_handler_;
};
NVSERV_END_NAMESPACE
#pragma once

#include <functional>
#include <memory>
#include <vector>

#include "nvserv/global.h"
#include "nvserv/http/middleware/middleware_base.h"

NVSERV_BEGIN_NAMESPACE(http::middleware)

class MiddlewareManager {
 public:
  void Add(std::shared_ptr<MiddlewareBase> middleware);
  void Handle(HttpRequest& req, HttpResponse& res);

 private:
  std::vector<std::shared_ptr<MiddlewareBase>> middlewares_;
};

NVSERV_END_NAMESPACE
#pragma once

#include <functional>
#include <memory>
#include <vector>

#include "nvserv/http/http_request.h"
#include "nvserv/http/http_response.h"
#include "nvserv/global.h"

NVSERV_BEGIN_NAMESPACE(http::middleware)

class MiddlewareBase {
 public:
  virtual ~MiddlewareBase() = default;
  virtual void Handle(HttpRequest& req, HttpResponse& res,
                      std::function<void()> next) = 0;
};

NVSERV_END_NAMESPACE
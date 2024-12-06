#pragma once

#include <chrono>
#include <ctime>
#include <functional>
#include <random>
#include <string>

#include "nvserv/global.h"
#include "nvserv/http/middleware/middleware_base.h"

NVSERV_BEGIN_NAMESPACE(http::middleware)

class CsrfMiddleware : public MiddlewareBase {
 public:
  CsrfMiddleware();
  void Handle(HttpRequest& req, HttpResponse& res,
              std::function<void()> next) override;

 private:
  std::string GenerateToken();
  bool ValidateToken(const std::string& token);

  std::string csrf_token_;
};

NVSERV_END_NAMESPACE
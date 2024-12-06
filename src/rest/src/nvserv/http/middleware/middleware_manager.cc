#include "nvserv/http/middleware/middleware_manager.h"

NVSERV_BEGIN_NAMESPACE(http::middleware)

void MiddlewareManager::Add(std::shared_ptr<MiddlewareBase> middleware) {
  middlewares_.push_back(middleware);
}

void MiddlewareManager::Handle(HttpRequest& req, HttpResponse& res) {
  std::function<void(size_t)> execute = [&](size_t index) {
    if (index < middlewares_.size()) {
      middlewares_[index]->Handle(req, res, [&]() { execute(index + 1); });
    }
  };
  execute(0);
}

NVSERV_END_NAMESPACE
#include "nvserv/route/route.h"

// cppcheck-suppress unknownMacro
NVREST_BEGIN_NAMESPACE(route)

Route::Route(const std::string& path, HandlerFn handler)
                : path_(std::string(path)), handler_(std::move(handler)) {}

const std::string& Route::Path() const {
  return path_;
}
const Route::HandlerFn& Route::Handler() const {
  return handler_;
}

NVREST_END_NAMESPACE

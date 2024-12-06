#include "nvserv/http/route.h"

// cppcheck-suppress unknownMacro
NVSERV_BEGIN_NAMESPACE(http)

Route::Route(const size_t key, const std::string& path,
             std::shared_ptr<handlers::HandlerBase> req_handler)
                : key_(key),
                  path_(std::string(path)),
                  req_handler_(req_handler) {}

const std::size_t& Route::Key() const {
  return key_;
}

const std::string& Route::Path() const {
  return path_;
}

const std::shared_ptr<handlers::HandlerBase> Route::RequestHandler() const {
  return req_handler_;
}

NVSERV_END_NAMESPACE

#pragma once

#include <nvserv/route/route.h>
#include <nvserv/route/router_node.h>
#include <nvserv/utils/string_utils.h>

#include <memory>
#include <regex>
#include <stdexcept>
#include <string>
#include <unordered_map>
#include <vector>

NVREST_BEGIN_NAMESPACE(route)
/// @brief Router class for managing routing endpoint registration and conform
/// to RFC-6570
class Router {
 public:
  Router();

  void AddRoute(const std::string& path, Route::HandlerFn handler);

  Route::HandlerFn MatchRoute(
      const std::string& path,
      std::unordered_map<std::string, std::string>& params) const;

 private:
  std::unique_ptr<RouterNode> root_;

  bool IsValidRoute(const std::string& path) const;
};
NVREST_END_NAMESPACE
#pragma once

#include <string>
#include <unordered_map>
#include <vector>
#include <stdexcept>
#include <string>
#include <nvserv/global_macro.h>
#include <functional>

NVREST_BEGIN_NAMESPACE(route)
class Route {
 public:
  using HandlerFn = std::function<void(const std::unordered_map<std::string, std::string>&)>;

  Route(const std::string& path, HandlerFn handler);

  const std::string& Path() const;
  const HandlerFn& Handler() const;

 private:
  std::string path_;
  HandlerFn handler_;
};

NVREST_END_NAMESPACE
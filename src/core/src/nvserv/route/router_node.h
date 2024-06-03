#pragma once
#include <memory>
#include <regex>
#include <stdexcept>
#include <string>
#include <unordered_map>
#include <vector>

#include "nvserv/global_macro.h"
#include "nvserv/route/declare.h"
#include "nvserv/route/route.h"

// cppcheck-suppress unknownMacro
NVREST_BEGIN_NAMESPACE(route)

/// @brief Radix Tree Node
struct RouterNode {
  std::unordered_map<std::string, std::unique_ptr<RouterNode>> children;
  Route::HandlerFn handler = nullptr;
  NodeType type = NodeType::kStatic;
  std::string param_name;
  std::regex param_regex;
};

NVREST_END_NAMESPACE
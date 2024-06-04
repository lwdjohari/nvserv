#pragma once
#include <memory>
#include <regex>
#include <stdexcept>
#include <string>
#include <unordered_map>
#include <vector>
#include <iostream>

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

  void PrintNode(const std::string& prefix = "") const {
    for (const auto& child : children) {
      std::cout << prefix << child.first;
      if (child.second->type == NodeType::kParameter) {
        std::cout << " (param: " << child.second->param_name << ")";
      }
      std::cout << std::endl;
      child.second->PrintNode(prefix + "  ");
    }
  }
};

NVREST_END_NAMESPACE
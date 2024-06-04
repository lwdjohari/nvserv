#include "nvserv/route/router.h"

#include <iostream>
// cppcheck-suppress unknownMacro
NVREST_BEGIN_NAMESPACE(route)
Router::Router() : root_(std::make_unique<RouterNode>()) {}

void Router::AddRoute(const std::string& path, Route::HandlerFn handler) {
  std::lock_guard<std::mutex> lock(mutex_); 
  if (!IsValidRoute(path)) {
    throw std::invalid_argument("Invalid route pattern: " + path);
  }

  std::vector<std::string> endpoint_parts;
  utils::string::SplitString(path, '/', [&](const std::string& part) {
    std::string cleaned_part = part;
    utils::string::RemoveSpacesRef(cleaned_part);  // Remove all spaces
    endpoint_parts.push_back(cleaned_part);
  });

  // Ensure at least one part is present
  if (endpoint_parts.empty()) {
    endpoint_parts.push_back("");
  }

  RouterNode* node = root_.get();
  size_t pos = 0;
  for (auto& part : endpoint_parts) {
    std::string normalized_part = part;

    if (normalized_part.front() == '{' && normalized_part.back() == '}') {
      normalized_part = "{}";  // Use a common key for parameters
    }

    if (node->children.find(normalized_part) == node->children.end()) {
      node->children[normalized_part] = std::make_unique<RouterNode>();
    }
    node = node->children[normalized_part].get();

    if (normalized_part == "{}") {
      node->param_name = part.substr(1, part.size() - 2);
      node->param_regex = std::regex("^[a-zA-Z0-9_-]+$");
      node->type = NodeType::kParameter;
    } else {
      node->type = NodeType::kStatic;
    }
  }

  node->handler = std::move(handler);
}

void Router::PrintRouterTree() const {
    std::cout << "Router Tree\n" << std::endl;
    std::cout << "Route Root:";

    root_->PrintNode("");
  }

Route::HandlerFn Router::MatchRoute(
    const std::string& path,
    std::unordered_map<std::string, std::string>& params) const {
  std::vector<std::string> endpoint_parts =
      utils::string::SplitString(path, '/');
  const RouterNode* node = root_.get();

  for (const auto& part : endpoint_parts) {
    auto it = node->children.find(part);
    if (it != node->children.end() && it->second->type == NodeType::kStatic) {
      node = it->second.get();
    } else {
      auto param_it = node->children.find("{}");
      if (param_it != node->children.end() &&
          param_it->second->type == NodeType::kParameter) {
        node = param_it->second.get();
        if (!std::regex_match(part, node->param_regex)) {
          return nullptr;  // Part does not match parameter pattern
        }
        params[node->param_name] = part;
      } else {
        return nullptr;  // No matching static or dynamic part
      }
    }
  }

  return node->handler;
}

bool Router::IsValidRoute(const std::string& path) const {
  static const std::regex valid_route_regex(
      R"(^(/[A-Za-z0-9-._~%!$&'()*+,;=:@{}]+)*$)");
  if (!std::regex_match(path, valid_route_regex)) {
    return false;  // Invalid characters in route or malformed path
  }

  size_t pos = 0;
  bool inside_param = false;
  while (pos < path.size()) {
    if (path[pos] == '{') {
      if (inside_param) {
        return false;  // Nested or consecutive '{' found
      }
      inside_param = true;
    } else if (path[pos] == '}') {
      if (!inside_param) {
        return false;  // Unmatched '}' found
      }
      inside_param = false;
      // Check for the next character after closing brace, it should not be
      // another '{'
      if (pos + 1 < path.size() && path[pos + 1] == '{') {
        return false;  // Consecutive parameter definitions without separator
      }
    }
    pos++;
  }
  return !inside_param;  // Ensure all '{' have matching '}'
}
NVREST_END_NAMESPACE
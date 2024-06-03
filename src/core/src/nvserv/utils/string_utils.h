#pragma once

#include <nvserv/global_macro.h>

#include <string>
#include <vector>
#include <functional>

// cppcheck-suppress unknownMacro
NVREST_BEGIN_NAMESPACE(utils::string)
inline std::vector<std::string> SplitString(const std::string& str,
                                            char delimiter) {
  std::vector<std::string> tokens;
  size_t start = 0;
  size_t end = str.find(delimiter);

  while (end != std::string::npos) {
    tokens.push_back(str.substr(start, end - start));
    start = end + 1;
    end = str.find(delimiter, start);
  }

  tokens.push_back(str.substr(start, end - start));
  return tokens;
}

inline void SplitString(const std::string& str, char delimiter,
                 const std::function<void(const std::string&)>& callback) {
  size_t start = 0;
  size_t end = str.find(delimiter);

  while (end != std::string::npos) {
    callback(str.substr(start, end - start));
    start = end + 1;
    end = str.find(delimiter, start);
  }

  callback(str.substr(start));
}

inline std::string RemoveSpaces(const std::string& str_to_clean) {
  auto str = std::string(str_to_clean);
  str.erase(std::remove_if(str.begin(), str.end(), ::isspace), str.end());
  return str;
}

inline void RemoveSpacesRef(std::string& str) {
    str.erase(std::remove_if(str.begin(), str.end(), ::isspace), str.end());
}
NVREST_END_NAMESPACE
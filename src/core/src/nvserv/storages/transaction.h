#pragma once

#include <any>
#include <chrono>
#include <ostream>
#include <tuple>
#include <utility>
#include <vector>

#include "nvserv/global_macro.h"
#include "nvserv/storages/declare.h"
NVREST_BEGIN_NAMESPACE(storages)

// Helper function to call a function with a tuple of arguments
template <typename Func, typename Tuple, std::size_t... I>
decltype(auto) callWithTuple(Func&& func, Tuple&& t,
                             std::index_sequence<I...>) {
  return func(std::get<I>(std::forward<Tuple>(t))...);
}

template <typename Func, typename Tuple>
decltype(auto) callWithTuple(Func&& func, Tuple&& t) {
  constexpr auto size = std::tuple_size<std::decay_t<Tuple>>::value;
  return callWithTuple(std::forward<Func>(func), std::forward<Tuple>(t),
                       std::make_index_sequence<size>{});
}

class Transaction {
 public:
  Transaction(){};
  virtual ~Transaction(){};

  // Template function to create a vector of std::any and call the virtual
  // function
  template <typename... Args>
  void Execute(const __NR_STRING_COMPAT_REF query, const Args&... args) {
    std::vector<std::any> anyArgs = {args...};
    ExecuteImpl(query, anyArgs);
  }

  virtual void Commit() = 0;
  virtual void Rollback() = 0;

 protected:
  // Non-template virtual function
  virtual void ExecuteImpl(const __NR_STRING_COMPAT_REF query,
                           const std::vector<std::any>& args) = 0;
};

NVREST_END_NAMESPACE
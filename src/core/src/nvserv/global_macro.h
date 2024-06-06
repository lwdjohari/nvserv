#pragma once

#if __cplusplus >= 201703L
#define __NR_CPP17 1
#else
#define __NR_CPP14 1
#endif

#if __NR_CPP17
#define __NR_RETURN_MOVE(arg) arg
#else
#define __NR_RETURN_MOVE(arg) std::move(arg)
#endif

#if __NR_CPP17
#include <string_view>
#endif

#if __NR_CPP17
#define __NR_STRING_COMPAT std::string_view
#else
#define __NR_STRING_COMPAT std::string
#endif

#if __NR_CPP17
#define __NR_STRING_COMPAT_REF std::string_view
#else
#define __NR_STRING_COMPAT_REF std::string&
#endif

#if __NR_CPP17
#define __NR_CONSTEXPR constexpr
#else
#define __NR_CONSTEXPR
#endif

#define NVREST_NAMESPACE namespace nvserv
#define NVREST_BEGIN_ROOT_NAMESPACE NVREST_NAMESPACE {
#define NVREST_BEGIN_NAMESPACE(arg) NVREST_NAMESPACE::arg {
#define NVREST_END_NAMESPACE }

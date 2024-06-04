#pragma once

#if __cplusplus >= 201703L
#ifndef __NR_CPP17
#define __NR_CPP17 1
#endif
#else
#ifndef __NR_CPP14 1
#define __NR_CPP14 1
#endif
#endif

#if __NR_CPP17
#ifndef __NR_RETURN_MOVE
#define __NR_RETURN_MOVE(arg) arg
#endif
#else
#ifndef __NR_RETURN_MOVE
#define __NR_RETURN_MOVE(arg) std::move(arg)
#endif
#endif

#if __NR_CPP17
#include <string_view>
#endif

#if __NR_CPP17
#ifndef __NR_STRING_COMPAT
#define __NR_STRING_COMPAT std::string_view
#endif
#else
#ifndef __NR_STRING_COMPAT
#define __NR_STRING_COMPAT std::string
#endif
#endif


#if __NR_CPP17
#ifndef __NR_CONSTEXPR
#define __NR_CONSTEXPR constexpr
#endif
#else
#ifndef __NR_CONSTEXPR
#define __NR_CONSTEXPR
#endif
#endif

#ifndef NVREST_NAMESPACE 
#define NVREST_NAMESPACE namespace nvserv
#endif

#ifndef NVREST_BEGIN_ROOT_NAMESPACE 
#define NVREST_BEGIN_ROOT_NAMESPACE NVREST_NAMESPACE{
#endif

#ifndef NVREST_BEGIN_NAMESPACE
#define NVREST_BEGIN_NAMESPACE(arg) NVREST_NAMESPACE::arg{
#endif

#ifndef NVREST_END_NAMESPACE 
#define NVREST_END_NAMESPACE }
#endif
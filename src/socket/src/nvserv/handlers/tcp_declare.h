#pragma once
#include <nvserv/global.h>

NVSERV_BEGIN_NAMESPACE(handlers)
enum class BufferType { STATIC, NODESTREAM };

enum class BufferFlushMethod { CALLBACK, FULL };


NVSERV_END_NAMESPACE
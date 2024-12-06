#pragma once

#include <memory>
#include "nvm/macro.h"
#include "nvserv/global_macro.h"

NVSERV_BEGIN_NAMESPACE(http)

enum class NodeType { kStatic, kParameter };
NVM_ENUM_CLASS_DISPLAY_TRAIT(NodeType)

class HttpServer;
using HttpServerPtr = std::shared_ptr<HttpServer>;
class HttpRequestContext;
class HttpRequest;

NVSERV_END_NAMESPACE


#pragma once

#include <memory>

#include "nvserv/global_macro.h"

NVSERV_BEGIN_NAMESPACE(http)

class HttpServer;
using HttpServerPtr = std::shared_ptr<HttpServer>;
class HttpRequestContext;
class HttpRequest;

NVSERV_END_NAMESPACE


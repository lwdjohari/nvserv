#pragma once

#include <memory>

#include "nvserv/global_macro.h"

NVREST_BEGIN_NAMESPACE(http)

class HttpServer;
using HttpServerPtr = std::shared_ptr<HttpServer>;
class HttpRequestContext;
class HttpRequest;

NVREST_END_NAMESPACE


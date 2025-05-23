#pragma once

#include <string>
#include <memory>
#include "nvm/macro.h"
#include "nvserv/global_macro.h"

NVSERV_BEGIN_NAMESPACE(http)

class Config;
using ConfigPtr = std::shared_ptr<Config>;

enum class HttpVersionMode {
    HTTP1_1,
    HTTP2,
    HTTP2_UPGRADE
};

enum class CompressionType {
    NONE,
    GZIP,
    BROTLI
};

enum class NodeType { kStatic, kParameter };
NVM_ENUM_CLASS_DISPLAY_TRAIT(NodeType)

class HttpServer;
using HttpServerPtr = std::shared_ptr<HttpServer>;
class HttpRequestContext;
class HttpRequest;

NVSERV_END_NAMESPACE


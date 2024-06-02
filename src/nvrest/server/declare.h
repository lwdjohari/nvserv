#pragma once

#include <memory>
namespace nvm::nvrest::server
{
    class HttpServer;
    using HttpServerPtr = std::shared_ptr<HttpServer>;

} // namespace nvm::nvrest::server

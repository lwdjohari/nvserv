#pragma once

#include <string>
#include <unordered_map>
#include <stdexcept>

#include "nvserv/http/declare.h"
#include "nvserv/global.h"
#include "nvserv/http/http_server_driver.h"

NVSERV_BEGIN_NAMESPACE(http)

class HttpRequest {
 public:
    explicit HttpRequest(HttpServerRequestDriver req); 

    std::string GetPath() const;
    std::string Method() const;
    std::unordered_map<std::string, std::string> Headers() const;
    std::string GetHeader(const std::string& name) const;
    std::string GetBody() const;
    std::string GetQueryString(const std::string& name) const;

 private:
    HttpServerRequestDriver req_;
};


NVSERV_END_NAMESPACE

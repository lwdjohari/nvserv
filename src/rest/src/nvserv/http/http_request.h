#pragma once

#include "piconaut/macro.h"
#include <string>
#include <unordered_map>
#include <h2o.h>
#include <stdexcept>

#include "nvserv/http/declare.h"

NVSERV_BEGIN_NAMESPACE(http)

class HttpRequest {
 public:
    explicit HttpRequest(h2o_req_t* req);

    std::string GetPath() const;
    std::string Method() const;
    std::unordered_map<std::string, std::string> Headers() const;
    std::string GetHeader(const std::string& name) const;
    std::string GetBody() const;
    std::string GetQueryString(const std::string& name) const;

 private:
    h2o_req_t* req_;
};


NVSERV_END_NAMESPACE

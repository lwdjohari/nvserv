#pragma once

#include <memory>
#include "nvserv/global.h"

NVSERV_BEGIN_NAMESPACE(http)

class HttpServerDriver{
    public:
        virtual ~HttpServerDriver();

    
};


class HttpServerRequestDriver{
    public:
        HttpServerRequestDriver(){}
        virtual ~HttpServerRequestDriver(){};

    
};

class HttpServerResponseDriver{
    public:
        HttpServerResponseDriver(){};
        virtual ~HttpServerResponseDriver(){};

    
};

using HttpServerDriverPtr = std::shared_ptr<HttpServerDriver>;
using HttpServerRequestDriverPtr = std::shared_ptr<HttpServerRequestDriver>;
using HttpServerResponseDriverPtr = std::shared_ptr<HttpServerResponseDriver>;

NVSERV_END_NAMESPACE
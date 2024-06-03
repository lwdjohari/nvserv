#pragma once
#include "nvserv/global_macro.h"
#include "nvm/macro.h"
#include "ostream"

NVREST_BEGIN_ROOT_NAMESPACE

enum class ServerType { Http2Auto, Http2, Http1, Grpc };

NVM_ENUM_CLASS_DISPLAY_TRAIT(ServerType)


NVREST_END_NAMESPACE


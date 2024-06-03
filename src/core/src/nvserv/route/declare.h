#pragma once

#include "nvserv/global_macro.h"
#include "nvm/macro.h"

//cppcheck-suppress unknownMacro
NVREST_BEGIN_NAMESPACE(route)

enum class NodeType { kStatic, kParameter };

NVM_ENUM_CLASS_DISPLAY_TRAIT(NodeType)

NVREST_END_NAMESPACE
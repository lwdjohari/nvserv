#pragma once

#include "nvserv/global_macro.h"
#include <nvm/macro.h>

// cppcheck-suppress unknownMacro
NVREST_BEGIN_NAMESPACE(logs)

enum class LogType{
    None = 0,
    Console = 1,
    File = 2,
    Custom = 4,
};

enum class LogLevel:int32_t{
    Trace = 0,
    Debug = 1,
    Info = 2,
    Warning = 3,
    Error = 4,
    Critical = 5
};

NVM_ENUM_CLASS_DISPLAY_TRAIT(LogLevel)


NVREST_END_NAMESPACE
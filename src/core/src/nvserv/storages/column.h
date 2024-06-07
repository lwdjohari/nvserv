#pragma once

#include <optional>
#include <string>
#include <any>
#include <typeindex>
#include <unordered_map>
#include <type_traits>
#include <stdexcept>
#include "nvserv/global_macro.h"


NVREST_BEGIN_NAMESPACE(storages)

class Column {
public:

    virtual ~Column() = default;


    virtual std::string Name() const{
        return std::string();
    };

protected:
    Column() = default;
    
};

NVREST_END_NAMESPACE
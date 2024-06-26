#pragma once

#include <pqxx/pqxx>

#include "nvserv/global_macro.h"
#include "nvserv/storages/column.h"

NVREST_BEGIN_NAMESPACE(storages::postgres)

class PgColumn : public Column {
public:
    explicit PgColumn(const pqxx::field& field) : field_(field) {}

    std::string Name() const override {
        return field_.name();
    }
    

protected:
    

private:
    pqxx::field field_;
};

NVREST_END_NAMESPACE
#pragma once

#include "nvserv/storages/postgres/declare.h"

NVREST_BEGIN_NAMESPACE(storages::postgres)

class PgServer{
    public:
        PgServer(){}
        ~PgServer(){}

    PgTransactionPtr Begin(){
        return nullptr;
    }
};

NVREST_END_NAMESPACE
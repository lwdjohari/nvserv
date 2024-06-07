#pragma once

#include "nvserv/global_macro.h"
#include "nvserv/storages/declare.h"
#include "chrono"

NVREST_BEGIN_NAMESPACE(storages)

class Connection
{    
public:
virtual ~Connection() = default;
    virtual TransactionPtr CreateTransaction() = 0;
    virtual void Open() = 0;
    virtual void Close() = 0;
    virtual void PingServer() = 0;
    virtual std::chrono::system_clock::time_point CreatedTime() const= 0;
    virtual std::chrono::system_clock::time_point AcquiredTime() const= 0;
    virtual std::chrono::milliseconds IdleDuration() const= 0;
    virtual void ReportHealth() const = 0;
    virtual bool IsOpen() const =0;
    virtual bool IsClusterConnected() const = 0;
    virtual bool IsIdle() const = 0;
    virtual void Release() = 0;
    virtual size_t GetHash() const = 0;
    StorageType Type() {
        return type_;
    }

protected:
    Connection(StorageType type){};
    StorageType type_;
};

NVREST_END_NAMESPACE
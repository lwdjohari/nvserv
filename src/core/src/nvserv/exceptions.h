#pragma once

#include <nvm/exceptions/exception.h>

#include "nvserv/global_macro.h"

NVREST_BEGIN_ROOT_NAMESPACE

using Exception = nvm::Exception;
using BadAllocationException = nvm::BadAllocationException;
using CastException = nvm::CastException;
using InvalidArgException = nvm::InvalidArgException;
using NullReferenceException = nvm::NullReferenceException;
using OutOfBoundException = nvm::OutOfBoundException;
using RuntimeException = nvm::RuntimeException;
using ThreadException = nvm::ThreadException;
using TypeException = nvm::TypeException;

NVREST_END_NAMESPACE
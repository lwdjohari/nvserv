#pragma once

#include <grpcpp/grpcpp.h>

#include <memory>

// Quick Macro to define Grpc RPC method in GrpcServiceHandler
// The implementation see the macro NV_GRPC_HANDLE_IMPL_METHOD_SCAFOLD_CREF.
// Use NV_GRPC_HANDLE_IMPL_METHOD_SCAFOLD_CREF and expend to write the
// implementation.
#define NV_GRPC_DEFINE_METHOD(service_class, method_name, request_type,   \
                              response_type)                              \
  grpc::Status method_name(grpc::ServerContext* context,                  \
                           const request_type* request,                   \
                           response_type* response) override {            \
    return this->HandleRequest<request_type, response_type>(              \
        context, request, response, &service_class::Handle##method_name); \
  }

// GRPC Template Handle Request.
// Must be implemented only one on GrpcServiceHandler as private
#define NV_GRPC_HANDLE_REQUEST_TEMPLATE()                                     \
  template <typename TReq, typename TRes, typename TFunc>                     \
  grpc::Status HandleRequest(grpc::ServerContext* context,                    \
                             const TReq* request, TRes* response, TFunc func) \
      const {                                                                 \
    *response = (this->*func)(*request);                                      \
    return grpc::Status::OK;                                                  \
  }

// Scafold GRPC Handle implementation with RequestType return type.
// Developer have to expand this macro and write the implementation.
#define NV_GRPC_HANDLE_IMPL_METHOD_SCAFOLD_CREF(MethodName, RequestType, \
                                                ReturnType)              \
  ReturnType MethodName(const RequestType& request) const {              \
    /* Implement your method here */                                     \
  }

// Scafold GRPC Handle implementation with std::shared_ptr<RequestType> return
// type. Developer have to expand this macro and write the implementation.
#define NV_GRPC_HANDLE_IMPL_SCAFOLD_CREF_SPTR(MethodName, RequestType,       \
                                              ReturnType)                    \
  std::shared_ptr<ReturnType> MethodName(const RequestType& request) const { \
    /* Implement your method here */                                         \
  }

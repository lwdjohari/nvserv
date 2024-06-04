#pragma once

#include <grpcpp/grpcpp.h>

#ifndef NVSERV_GRPC_DEFINE_HANDLER
#define NVSERV_GRPC_DEFINE_HANDLER(HandlerName, RequestType, ResponseType)   \
  class HandlerName : public GrpcServiceHandler<RequestType, ResponseType> { \
   public:                                                                   \
    using GrpcServiceHandler::GrpcServiceHandler;                            \
                                                                             \
   protected:                                                                \
    void HandleServiceImpl(const RequestType& request,                       \
                           ResponseType& response) const override {          \
      /* Implement business logic here */                                    \
    }                                                                        \
  }
#endif

#define NV_GRPC_DEFINE_METHOD(service_class, method_name, request_type, \
                                   response_type)                            \
  grpc::Status method_name(grpc::ServerContext* context,                     \
                           const request_type* request,                      \
                           response_type* response) override {               \
    return this->HandleRequest<request_type, response_type>(                 \
        context, request, response, &service_class::Handle##method_name);    \
  }

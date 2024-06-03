#pragma once

#pragma once

#define NVSERV_GRPC_DEFINE_HANDLER(HandlerName, RequestType, ResponseType)    \
  class HandlerName : public GrpcServiceHandler<RequestType, ResponseType> { \
   public:                                                                   \
    using GrpcServiceHandler::GrpcServiceHandler;                            \
                                                                             \
   protected:                                                                \
    void HandleServiceImpl(const RequestType& request,                     \
                             ResponseType& response) const override {        \
      /* Implement business logic here */                                    \
    }                                                                        \
  }
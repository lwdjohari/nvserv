#pragma once

#include "nvserv/global_macro.h"
#include "nvserv/handlers/grpc_service_handler_base.h"
#include "grpcpp/proto_utils.h"

NVREST_BEGIN_NAMESPACE(handlers)

template <typename RequestType, typename ResponseType>
class GrpcServiceHandler : public GrpcServiceHandlerBase {
 public:
  using GrpcServiceHandlerBase::GrpcServiceHandlerBase;

 protected:
  void HandleRequest(grpc::ServerContext* context,
                     const grpc::ByteBuffer* request,
                     grpc::ByteBuffer* response) const override {
    RequestType req;
    ResponseType resp;

    // Parse the request
    grpc::ProtoUtils::Parse(request, &req);

    // Handle the request and populate the response
    HandleServiceImpl(req, resp);

    // Serialize the response
    grpc::ProtoUtils::Serialize(resp, response);
  }

  virtual void HandleServiceImpl(const RequestType& request,
                                   ResponseType& response) const = 0;
};

NVREST_END_NAMESPACE
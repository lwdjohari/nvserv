#include "nvserv/handlers/grpc_service_handler.h"

NVSERV_BEGIN_NAMESPACE(handlers)

 RpcMethodHandlerBase::RpcMethodHandlerBase() {}
 RpcMethodHandlerBase::~RpcMethodHandlerBase() {}

grpc::Status RpcMethodHandlerBase::HandleRequest(grpc::ServerContext* context,
                           const grpc::ByteBuffer* request,
                           grpc::ByteBuffer* response) {
  return grpc::Status(grpc::StatusCode::UNKNOWN,"Please override method `HandleRequest` to use it properly");
}
NVSERV_END_NAMESPACE
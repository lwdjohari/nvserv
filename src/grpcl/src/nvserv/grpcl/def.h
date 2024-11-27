#pragma once

#include <iostream>

#include <grpcpp/grpcpp.h>
#include "nvserv/global_macro.h"

NVSERV_BEGIN_NAMESPACE(grpcl)

// template <typename T>
// grpc::Status Serialize(const T& message, grpc::ByteBuffer* buffer) {
//   return grpc::Serialize(message, buffer);
// }

// template <typename T>
// grpc::Status Deserialize(const grpc::ByteBuffer* buffer, T* message) {
//   return grpc::ProtoUtils::Parse(buffer, message);
// }

// template <typename RequestType, typename ResponseType, typename Handler>
// grpc::Status HandleGrpcCall(grpc::ServerContext* context,
//                             const RequestType* request, ResponseType* response,
//                             const Handler& handler) {
//   grpc::ByteBuffer request_buf, response_buf;

//   // Serialize the request
//   grpc::Status serialize_status = Serialize(*request, &request_buf);
//   if (!serialize_status.ok()) {
//     return serialize_status;
//   }

//   // Call the handler
//   grpc::Status handler_status =
//       handler.HandleRequest(context, &request_buf, &response_buf);
//   if (!handler_status.ok()) {
//     return handler_status;
//   }

//   // Parse the response
//   grpc::Status parse_status = Deserialize(&response_buf, response);
//   return parse_status.ok() ? grpc::Status::OK : parse_status;
// }

// class ErrorUtil {
//  public:
//   static grpc::Status GenerateErrorStatus(grpc::StatusCode code,
//                                           const std::string& message) {
//     // Log the error message
//     std::cerr << "Error: " << message << std::endl;
//     return grpc::Status(code, message);
//   }
// };

NVSERV_END_NAMESPACE

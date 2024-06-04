#pragma once

#include <grpcpp/grpcpp.h>
#include <nvserv/global_macro.h>

#include <iostream>
#include <tuple>
#include <utility>

#include "nvserv/components/component_config.h"
#include "nvserv/components/component_locator.h"

NVREST_BEGIN_NAMESPACE(handlers)

class GrpcServiceHandlerBase {
 public:
  virtual ~GrpcServiceHandlerBase() = default;
  // Pure virtual method to handle the gRPC request
  virtual grpc::Status HandleRequest(grpc::ServerContext* context,
                                     const grpc::ByteBuffer* request,
                                     grpc::ByteBuffer* response) const = 0;
};

template <typename TRequestType, typename TResponseType>
class GrpcServiceHandler : public GrpcServiceHandlerBase {
 public:
  GrpcServiceHandler(grpc::ServerContext* context,
                     const grpc::ByteBuffer* request,
                     grpc::ByteBuffer* response){};
  virtual ~GrpcServiceHandler(){};

 protected:
  grpc::Status HandleRequest(grpc::ServerContext* context,
                             const grpc::ByteBuffer* request,
                             grpc::ByteBuffer* response) const override {
    TRequestType req;
    grpc::Status status = Deserialize(request, &req);
    if (!status.ok()) {
      return status;
    }

    TResponseType resp = HandleServiceImpl(context, req);

    status = Serialize(resp, response);
    if (!status.ok()) {
      return status;
    }

    return grpc::Status::OK;
  }

 private:
  grpc::Status Deserialize(const grpc::ByteBuffer* buffer,
                           TRequestType* message) const {
    std::vector<grpc::Slice> slices;
    if (buffer->Dump(&slices).ok()) {
      std::string data;
      for (const auto& slice : slices) {
        data.append(reinterpret_cast<const char*>(slice.begin()), slice.size());
      }
      if (message->ParseFromString(data)) {
        return grpc::Status::OK;
      } else {
        return grpc::Status(grpc::StatusCode::INTERNAL,
                            "Failed to parse request message");
      }
    }
    return grpc::Status(grpc::StatusCode::INTERNAL,
                        "Failed to deserialize message");
  }

  grpc::Status Serialize(const TResponseType& message,
                         grpc::ByteBuffer* buffer) const {
    std::string serialized_data;
    if (message.SerializeToString(&serialized_data)) {
      grpc::Slice slice(serialized_data);
      *buffer = grpc::ByteBuffer(&slice, 1);
      return grpc::Status::OK;
    } else {
      return grpc::Status(grpc::StatusCode::INTERNAL,
                          "Failed to serialize response message");
    }
  }
};

// template <typename RequestType, typename ResponseType>
// class GrpcServiceHandler : public GrpcServiceHandlerBase {
//  public:
//   // using GrpcServiceHandlerBase::GrpcServiceHandlerBase;
//   using RequestTuple = std::tuple<RequestType, ResponseType>;

//  protected:
//   // Handle unary request with multiple gRPC messages
//   void HandleRequest(grpc::ServerContext* context,
//                      const grpc::ByteBuffer* request,
//                      grpc::ByteBuffer* response) const override {
//     RequestTuple requests;
//     DeserializeMessages(request, requests);

//     auto resp = HandleServiceImpl(context, requests);

//     // grpc::ProtoUtils::Serialize(resp, response);
//   }

//   virtual auto HandleServiceImpl(grpc::ServerContext* context,
//                                  const RequestTuple& requests) const
//       -> decltype(std::apply(
//              [this](auto&&... args) { return this->HandleService(args...); },
//              requests)) = 0;

//  private:
//   template <std::size_t Index = 0>
//   void DeserializeMessages(const grpc::ByteBuffer* buffer,
//                            RequestTuple& requests) const {
//     if constexpr (Index < std::tuple_size_v<RequestTuple>) {
//       using MessageType = std::tuple_element_t<Index, RequestTuple>;
//       MessageType message;
//       // grpc::ProtoUtils::Parse(buffer, &message);
//       std::get<Index>(requests) = message;
//       DeserializeMessages<Index + 1>(buffer, requests);
//     }
//   }
// };

NVREST_END_NAMESPACE
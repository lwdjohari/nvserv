// Generated by the gRPC C++ plugin.
// If you make any local change, they will be lost.
// source: order_service.proto

#include "order_service.pb.h"
#include "order_service.grpc.pb.h"

#include <functional>
#include <grpcpp/support/async_stream.h>
#include <grpcpp/support/async_unary_call.h>
#include <grpcpp/impl/channel_interface.h>
#include <grpcpp/impl/client_unary_call.h>
#include <grpcpp/support/client_callback.h>
#include <grpcpp/support/message_allocator.h>
#include <grpcpp/support/method_handler.h>
#include <grpcpp/impl/rpc_service_method.h>
#include <grpcpp/support/server_callback.h>
#include <grpcpp/impl/server_callback_handlers.h>
#include <grpcpp/server_context.h>
#include <grpcpp/impl/service_type.h>
#include <grpcpp/support/sync_stream.h>
namespace orderservice {

static const char* OrderService_method_names[] = {
  "/orderservice.OrderService/Order",
  "/orderservice.OrderService/VoidMethod",
};

std::unique_ptr< OrderService::Stub> OrderService::NewStub(const std::shared_ptr< ::grpc::ChannelInterface>& channel, const ::grpc::StubOptions& options) {
  (void)options;
  std::unique_ptr< OrderService::Stub> stub(new OrderService::Stub(channel, options));
  return stub;
}

OrderService::Stub::Stub(const std::shared_ptr< ::grpc::ChannelInterface>& channel, const ::grpc::StubOptions& options)
  : channel_(channel), rpcmethod_Order_(OrderService_method_names[0], options.suffix_for_stats(),::grpc::internal::RpcMethod::NORMAL_RPC, channel)
  , rpcmethod_VoidMethod_(OrderService_method_names[1], options.suffix_for_stats(),::grpc::internal::RpcMethod::NORMAL_RPC, channel)
  {}

::grpc::Status OrderService::Stub::Order(::grpc::ClientContext* context, const ::orderservice::OrderRequest& request, ::orderservice::OrderResult* response) {
  return ::grpc::internal::BlockingUnaryCall< ::orderservice::OrderRequest, ::orderservice::OrderResult, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(channel_.get(), rpcmethod_Order_, context, request, response);
}

void OrderService::Stub::async::Order(::grpc::ClientContext* context, const ::orderservice::OrderRequest* request, ::orderservice::OrderResult* response, std::function<void(::grpc::Status)> f) {
  ::grpc::internal::CallbackUnaryCall< ::orderservice::OrderRequest, ::orderservice::OrderResult, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(stub_->channel_.get(), stub_->rpcmethod_Order_, context, request, response, std::move(f));
}

void OrderService::Stub::async::Order(::grpc::ClientContext* context, const ::orderservice::OrderRequest* request, ::orderservice::OrderResult* response, ::grpc::ClientUnaryReactor* reactor) {
  ::grpc::internal::ClientCallbackUnaryFactory::Create< ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(stub_->channel_.get(), stub_->rpcmethod_Order_, context, request, response, reactor);
}

::grpc::ClientAsyncResponseReader< ::orderservice::OrderResult>* OrderService::Stub::PrepareAsyncOrderRaw(::grpc::ClientContext* context, const ::orderservice::OrderRequest& request, ::grpc::CompletionQueue* cq) {
  return ::grpc::internal::ClientAsyncResponseReaderHelper::Create< ::orderservice::OrderResult, ::orderservice::OrderRequest, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(channel_.get(), cq, rpcmethod_Order_, context, request);
}

::grpc::ClientAsyncResponseReader< ::orderservice::OrderResult>* OrderService::Stub::AsyncOrderRaw(::grpc::ClientContext* context, const ::orderservice::OrderRequest& request, ::grpc::CompletionQueue* cq) {
  auto* result =
    this->PrepareAsyncOrderRaw(context, request, cq);
  result->StartCall();
  return result;
}

::grpc::Status OrderService::Stub::VoidMethod(::grpc::ClientContext* context, const ::orderservice::Void& request, ::orderservice::Void* response) {
  return ::grpc::internal::BlockingUnaryCall< ::orderservice::Void, ::orderservice::Void, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(channel_.get(), rpcmethod_VoidMethod_, context, request, response);
}

void OrderService::Stub::async::VoidMethod(::grpc::ClientContext* context, const ::orderservice::Void* request, ::orderservice::Void* response, std::function<void(::grpc::Status)> f) {
  ::grpc::internal::CallbackUnaryCall< ::orderservice::Void, ::orderservice::Void, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(stub_->channel_.get(), stub_->rpcmethod_VoidMethod_, context, request, response, std::move(f));
}

void OrderService::Stub::async::VoidMethod(::grpc::ClientContext* context, const ::orderservice::Void* request, ::orderservice::Void* response, ::grpc::ClientUnaryReactor* reactor) {
  ::grpc::internal::ClientCallbackUnaryFactory::Create< ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(stub_->channel_.get(), stub_->rpcmethod_VoidMethod_, context, request, response, reactor);
}

::grpc::ClientAsyncResponseReader< ::orderservice::Void>* OrderService::Stub::PrepareAsyncVoidMethodRaw(::grpc::ClientContext* context, const ::orderservice::Void& request, ::grpc::CompletionQueue* cq) {
  return ::grpc::internal::ClientAsyncResponseReaderHelper::Create< ::orderservice::Void, ::orderservice::Void, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(channel_.get(), cq, rpcmethod_VoidMethod_, context, request);
}

::grpc::ClientAsyncResponseReader< ::orderservice::Void>* OrderService::Stub::AsyncVoidMethodRaw(::grpc::ClientContext* context, const ::orderservice::Void& request, ::grpc::CompletionQueue* cq) {
  auto* result =
    this->PrepareAsyncVoidMethodRaw(context, request, cq);
  result->StartCall();
  return result;
}

OrderService::Service::Service() {
  AddMethod(new ::grpc::internal::RpcServiceMethod(
      OrderService_method_names[0],
      ::grpc::internal::RpcMethod::NORMAL_RPC,
      new ::grpc::internal::RpcMethodHandler< OrderService::Service, ::orderservice::OrderRequest, ::orderservice::OrderResult, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(
          [](OrderService::Service* service,
             ::grpc::ServerContext* ctx,
             const ::orderservice::OrderRequest* req,
             ::orderservice::OrderResult* resp) {
               return service->Order(ctx, req, resp);
             }, this)));
  AddMethod(new ::grpc::internal::RpcServiceMethod(
      OrderService_method_names[1],
      ::grpc::internal::RpcMethod::NORMAL_RPC,
      new ::grpc::internal::RpcMethodHandler< OrderService::Service, ::orderservice::Void, ::orderservice::Void, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(
          [](OrderService::Service* service,
             ::grpc::ServerContext* ctx,
             const ::orderservice::Void* req,
             ::orderservice::Void* resp) {
               return service->VoidMethod(ctx, req, resp);
             }, this)));
}

OrderService::Service::~Service() {
}

::grpc::Status OrderService::Service::Order(::grpc::ServerContext* context, const ::orderservice::OrderRequest* request, ::orderservice::OrderResult* response) {
  (void) context;
  (void) request;
  (void) response;
  return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
}

::grpc::Status OrderService::Service::VoidMethod(::grpc::ServerContext* context, const ::orderservice::Void* request, ::orderservice::Void* response) {
  (void) context;
  (void) request;
  (void) response;
  return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
}


}  // namespace orderservice


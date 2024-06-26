// Generated by the gRPC C++ plugin.
// If you make any local change, they will be lost.
// source: order_service.proto
#ifndef GRPC_order_5fservice_2eproto__INCLUDED
#define GRPC_order_5fservice_2eproto__INCLUDED

#include "order_service.pb.h"

#include <functional>
#include <grpcpp/generic/async_generic_service.h>
#include <grpcpp/support/async_stream.h>
#include <grpcpp/support/async_unary_call.h>
#include <grpcpp/support/client_callback.h>
#include <grpcpp/client_context.h>
#include <grpcpp/completion_queue.h>
#include <grpcpp/support/message_allocator.h>
#include <grpcpp/support/method_handler.h>
#include <grpcpp/impl/proto_utils.h>
#include <grpcpp/impl/rpc_method.h>
#include <grpcpp/support/server_callback.h>
#include <grpcpp/impl/server_callback_handlers.h>
#include <grpcpp/server_context.h>
#include <grpcpp/impl/service_type.h>
#include <grpcpp/support/status.h>
#include <grpcpp/support/stub_options.h>
#include <grpcpp/support/sync_stream.h>

namespace orderservice {

class OrderService final {
 public:
  static constexpr char const* service_full_name() {
    return "orderservice.OrderService";
  }
  class StubInterface {
   public:
    virtual ~StubInterface() {}
    virtual ::grpc::Status Order(::grpc::ClientContext* context, const ::orderservice::OrderRequest& request, ::orderservice::OrderResult* response) = 0;
    std::unique_ptr< ::grpc::ClientAsyncResponseReaderInterface< ::orderservice::OrderResult>> AsyncOrder(::grpc::ClientContext* context, const ::orderservice::OrderRequest& request, ::grpc::CompletionQueue* cq) {
      return std::unique_ptr< ::grpc::ClientAsyncResponseReaderInterface< ::orderservice::OrderResult>>(AsyncOrderRaw(context, request, cq));
    }
    std::unique_ptr< ::grpc::ClientAsyncResponseReaderInterface< ::orderservice::OrderResult>> PrepareAsyncOrder(::grpc::ClientContext* context, const ::orderservice::OrderRequest& request, ::grpc::CompletionQueue* cq) {
      return std::unique_ptr< ::grpc::ClientAsyncResponseReaderInterface< ::orderservice::OrderResult>>(PrepareAsyncOrderRaw(context, request, cq));
    }
    virtual ::grpc::Status VoidMethod(::grpc::ClientContext* context, const ::orderservice::Void& request, ::orderservice::Void* response) = 0;
    std::unique_ptr< ::grpc::ClientAsyncResponseReaderInterface< ::orderservice::Void>> AsyncVoidMethod(::grpc::ClientContext* context, const ::orderservice::Void& request, ::grpc::CompletionQueue* cq) {
      return std::unique_ptr< ::grpc::ClientAsyncResponseReaderInterface< ::orderservice::Void>>(AsyncVoidMethodRaw(context, request, cq));
    }
    std::unique_ptr< ::grpc::ClientAsyncResponseReaderInterface< ::orderservice::Void>> PrepareAsyncVoidMethod(::grpc::ClientContext* context, const ::orderservice::Void& request, ::grpc::CompletionQueue* cq) {
      return std::unique_ptr< ::grpc::ClientAsyncResponseReaderInterface< ::orderservice::Void>>(PrepareAsyncVoidMethodRaw(context, request, cq));
    }
    class async_interface {
     public:
      virtual ~async_interface() {}
      virtual void Order(::grpc::ClientContext* context, const ::orderservice::OrderRequest* request, ::orderservice::OrderResult* response, std::function<void(::grpc::Status)>) = 0;
      virtual void Order(::grpc::ClientContext* context, const ::orderservice::OrderRequest* request, ::orderservice::OrderResult* response, ::grpc::ClientUnaryReactor* reactor) = 0;
      virtual void VoidMethod(::grpc::ClientContext* context, const ::orderservice::Void* request, ::orderservice::Void* response, std::function<void(::grpc::Status)>) = 0;
      virtual void VoidMethod(::grpc::ClientContext* context, const ::orderservice::Void* request, ::orderservice::Void* response, ::grpc::ClientUnaryReactor* reactor) = 0;
    };
    typedef class async_interface experimental_async_interface;
    virtual class async_interface* async() { return nullptr; }
    class async_interface* experimental_async() { return async(); }
   private:
    virtual ::grpc::ClientAsyncResponseReaderInterface< ::orderservice::OrderResult>* AsyncOrderRaw(::grpc::ClientContext* context, const ::orderservice::OrderRequest& request, ::grpc::CompletionQueue* cq) = 0;
    virtual ::grpc::ClientAsyncResponseReaderInterface< ::orderservice::OrderResult>* PrepareAsyncOrderRaw(::grpc::ClientContext* context, const ::orderservice::OrderRequest& request, ::grpc::CompletionQueue* cq) = 0;
    virtual ::grpc::ClientAsyncResponseReaderInterface< ::orderservice::Void>* AsyncVoidMethodRaw(::grpc::ClientContext* context, const ::orderservice::Void& request, ::grpc::CompletionQueue* cq) = 0;
    virtual ::grpc::ClientAsyncResponseReaderInterface< ::orderservice::Void>* PrepareAsyncVoidMethodRaw(::grpc::ClientContext* context, const ::orderservice::Void& request, ::grpc::CompletionQueue* cq) = 0;
  };
  class Stub final : public StubInterface {
   public:
    Stub(const std::shared_ptr< ::grpc::ChannelInterface>& channel, const ::grpc::StubOptions& options = ::grpc::StubOptions());
    ::grpc::Status Order(::grpc::ClientContext* context, const ::orderservice::OrderRequest& request, ::orderservice::OrderResult* response) override;
    std::unique_ptr< ::grpc::ClientAsyncResponseReader< ::orderservice::OrderResult>> AsyncOrder(::grpc::ClientContext* context, const ::orderservice::OrderRequest& request, ::grpc::CompletionQueue* cq) {
      return std::unique_ptr< ::grpc::ClientAsyncResponseReader< ::orderservice::OrderResult>>(AsyncOrderRaw(context, request, cq));
    }
    std::unique_ptr< ::grpc::ClientAsyncResponseReader< ::orderservice::OrderResult>> PrepareAsyncOrder(::grpc::ClientContext* context, const ::orderservice::OrderRequest& request, ::grpc::CompletionQueue* cq) {
      return std::unique_ptr< ::grpc::ClientAsyncResponseReader< ::orderservice::OrderResult>>(PrepareAsyncOrderRaw(context, request, cq));
    }
    ::grpc::Status VoidMethod(::grpc::ClientContext* context, const ::orderservice::Void& request, ::orderservice::Void* response) override;
    std::unique_ptr< ::grpc::ClientAsyncResponseReader< ::orderservice::Void>> AsyncVoidMethod(::grpc::ClientContext* context, const ::orderservice::Void& request, ::grpc::CompletionQueue* cq) {
      return std::unique_ptr< ::grpc::ClientAsyncResponseReader< ::orderservice::Void>>(AsyncVoidMethodRaw(context, request, cq));
    }
    std::unique_ptr< ::grpc::ClientAsyncResponseReader< ::orderservice::Void>> PrepareAsyncVoidMethod(::grpc::ClientContext* context, const ::orderservice::Void& request, ::grpc::CompletionQueue* cq) {
      return std::unique_ptr< ::grpc::ClientAsyncResponseReader< ::orderservice::Void>>(PrepareAsyncVoidMethodRaw(context, request, cq));
    }
    class async final :
      public StubInterface::async_interface {
     public:
      void Order(::grpc::ClientContext* context, const ::orderservice::OrderRequest* request, ::orderservice::OrderResult* response, std::function<void(::grpc::Status)>) override;
      void Order(::grpc::ClientContext* context, const ::orderservice::OrderRequest* request, ::orderservice::OrderResult* response, ::grpc::ClientUnaryReactor* reactor) override;
      void VoidMethod(::grpc::ClientContext* context, const ::orderservice::Void* request, ::orderservice::Void* response, std::function<void(::grpc::Status)>) override;
      void VoidMethod(::grpc::ClientContext* context, const ::orderservice::Void* request, ::orderservice::Void* response, ::grpc::ClientUnaryReactor* reactor) override;
     private:
      friend class Stub;
      explicit async(Stub* stub): stub_(stub) { }
      Stub* stub() { return stub_; }
      Stub* stub_;
    };
    class async* async() override { return &async_stub_; }

   private:
    std::shared_ptr< ::grpc::ChannelInterface> channel_;
    class async async_stub_{this};
    ::grpc::ClientAsyncResponseReader< ::orderservice::OrderResult>* AsyncOrderRaw(::grpc::ClientContext* context, const ::orderservice::OrderRequest& request, ::grpc::CompletionQueue* cq) override;
    ::grpc::ClientAsyncResponseReader< ::orderservice::OrderResult>* PrepareAsyncOrderRaw(::grpc::ClientContext* context, const ::orderservice::OrderRequest& request, ::grpc::CompletionQueue* cq) override;
    ::grpc::ClientAsyncResponseReader< ::orderservice::Void>* AsyncVoidMethodRaw(::grpc::ClientContext* context, const ::orderservice::Void& request, ::grpc::CompletionQueue* cq) override;
    ::grpc::ClientAsyncResponseReader< ::orderservice::Void>* PrepareAsyncVoidMethodRaw(::grpc::ClientContext* context, const ::orderservice::Void& request, ::grpc::CompletionQueue* cq) override;
    const ::grpc::internal::RpcMethod rpcmethod_Order_;
    const ::grpc::internal::RpcMethod rpcmethod_VoidMethod_;
  };
  static std::unique_ptr<Stub> NewStub(const std::shared_ptr< ::grpc::ChannelInterface>& channel, const ::grpc::StubOptions& options = ::grpc::StubOptions());

  class Service : public ::grpc::Service {
   public:
    Service();
    virtual ~Service();
    virtual ::grpc::Status Order(::grpc::ServerContext* context, const ::orderservice::OrderRequest* request, ::orderservice::OrderResult* response);
    virtual ::grpc::Status VoidMethod(::grpc::ServerContext* context, const ::orderservice::Void* request, ::orderservice::Void* response);
  };
  template <class BaseClass>
  class WithAsyncMethod_Order : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(const Service* /*service*/) {}
   public:
    WithAsyncMethod_Order() {
      ::grpc::Service::MarkMethodAsync(0);
    }
    ~WithAsyncMethod_Order() override {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable synchronous version of this method
    ::grpc::Status Order(::grpc::ServerContext* /*context*/, const ::orderservice::OrderRequest* /*request*/, ::orderservice::OrderResult* /*response*/) override {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
    void RequestOrder(::grpc::ServerContext* context, ::orderservice::OrderRequest* request, ::grpc::ServerAsyncResponseWriter< ::orderservice::OrderResult>* response, ::grpc::CompletionQueue* new_call_cq, ::grpc::ServerCompletionQueue* notification_cq, void *tag) {
      ::grpc::Service::RequestAsyncUnary(0, context, request, response, new_call_cq, notification_cq, tag);
    }
  };
  template <class BaseClass>
  class WithAsyncMethod_VoidMethod : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(const Service* /*service*/) {}
   public:
    WithAsyncMethod_VoidMethod() {
      ::grpc::Service::MarkMethodAsync(1);
    }
    ~WithAsyncMethod_VoidMethod() override {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable synchronous version of this method
    ::grpc::Status VoidMethod(::grpc::ServerContext* /*context*/, const ::orderservice::Void* /*request*/, ::orderservice::Void* /*response*/) override {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
    void RequestVoidMethod(::grpc::ServerContext* context, ::orderservice::Void* request, ::grpc::ServerAsyncResponseWriter< ::orderservice::Void>* response, ::grpc::CompletionQueue* new_call_cq, ::grpc::ServerCompletionQueue* notification_cq, void *tag) {
      ::grpc::Service::RequestAsyncUnary(1, context, request, response, new_call_cq, notification_cq, tag);
    }
  };
  typedef WithAsyncMethod_Order<WithAsyncMethod_VoidMethod<Service > > AsyncService;
  template <class BaseClass>
  class WithCallbackMethod_Order : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(const Service* /*service*/) {}
   public:
    WithCallbackMethod_Order() {
      ::grpc::Service::MarkMethodCallback(0,
          new ::grpc::internal::CallbackUnaryHandler< ::orderservice::OrderRequest, ::orderservice::OrderResult>(
            [this](
                   ::grpc::CallbackServerContext* context, const ::orderservice::OrderRequest* request, ::orderservice::OrderResult* response) { return this->Order(context, request, response); }));}
    void SetMessageAllocatorFor_Order(
        ::grpc::MessageAllocator< ::orderservice::OrderRequest, ::orderservice::OrderResult>* allocator) {
      ::grpc::internal::MethodHandler* const handler = ::grpc::Service::GetHandler(0);
      static_cast<::grpc::internal::CallbackUnaryHandler< ::orderservice::OrderRequest, ::orderservice::OrderResult>*>(handler)
              ->SetMessageAllocator(allocator);
    }
    ~WithCallbackMethod_Order() override {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable synchronous version of this method
    ::grpc::Status Order(::grpc::ServerContext* /*context*/, const ::orderservice::OrderRequest* /*request*/, ::orderservice::OrderResult* /*response*/) override {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
    virtual ::grpc::ServerUnaryReactor* Order(
      ::grpc::CallbackServerContext* /*context*/, const ::orderservice::OrderRequest* /*request*/, ::orderservice::OrderResult* /*response*/)  { return nullptr; }
  };
  template <class BaseClass>
  class WithCallbackMethod_VoidMethod : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(const Service* /*service*/) {}
   public:
    WithCallbackMethod_VoidMethod() {
      ::grpc::Service::MarkMethodCallback(1,
          new ::grpc::internal::CallbackUnaryHandler< ::orderservice::Void, ::orderservice::Void>(
            [this](
                   ::grpc::CallbackServerContext* context, const ::orderservice::Void* request, ::orderservice::Void* response) { return this->VoidMethod(context, request, response); }));}
    void SetMessageAllocatorFor_VoidMethod(
        ::grpc::MessageAllocator< ::orderservice::Void, ::orderservice::Void>* allocator) {
      ::grpc::internal::MethodHandler* const handler = ::grpc::Service::GetHandler(1);
      static_cast<::grpc::internal::CallbackUnaryHandler< ::orderservice::Void, ::orderservice::Void>*>(handler)
              ->SetMessageAllocator(allocator);
    }
    ~WithCallbackMethod_VoidMethod() override {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable synchronous version of this method
    ::grpc::Status VoidMethod(::grpc::ServerContext* /*context*/, const ::orderservice::Void* /*request*/, ::orderservice::Void* /*response*/) override {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
    virtual ::grpc::ServerUnaryReactor* VoidMethod(
      ::grpc::CallbackServerContext* /*context*/, const ::orderservice::Void* /*request*/, ::orderservice::Void* /*response*/)  { return nullptr; }
  };
  typedef WithCallbackMethod_Order<WithCallbackMethod_VoidMethod<Service > > CallbackService;
  typedef CallbackService ExperimentalCallbackService;
  template <class BaseClass>
  class WithGenericMethod_Order : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(const Service* /*service*/) {}
   public:
    WithGenericMethod_Order() {
      ::grpc::Service::MarkMethodGeneric(0);
    }
    ~WithGenericMethod_Order() override {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable synchronous version of this method
    ::grpc::Status Order(::grpc::ServerContext* /*context*/, const ::orderservice::OrderRequest* /*request*/, ::orderservice::OrderResult* /*response*/) override {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
  };
  template <class BaseClass>
  class WithGenericMethod_VoidMethod : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(const Service* /*service*/) {}
   public:
    WithGenericMethod_VoidMethod() {
      ::grpc::Service::MarkMethodGeneric(1);
    }
    ~WithGenericMethod_VoidMethod() override {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable synchronous version of this method
    ::grpc::Status VoidMethod(::grpc::ServerContext* /*context*/, const ::orderservice::Void* /*request*/, ::orderservice::Void* /*response*/) override {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
  };
  template <class BaseClass>
  class WithRawMethod_Order : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(const Service* /*service*/) {}
   public:
    WithRawMethod_Order() {
      ::grpc::Service::MarkMethodRaw(0);
    }
    ~WithRawMethod_Order() override {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable synchronous version of this method
    ::grpc::Status Order(::grpc::ServerContext* /*context*/, const ::orderservice::OrderRequest* /*request*/, ::orderservice::OrderResult* /*response*/) override {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
    void RequestOrder(::grpc::ServerContext* context, ::grpc::ByteBuffer* request, ::grpc::ServerAsyncResponseWriter< ::grpc::ByteBuffer>* response, ::grpc::CompletionQueue* new_call_cq, ::grpc::ServerCompletionQueue* notification_cq, void *tag) {
      ::grpc::Service::RequestAsyncUnary(0, context, request, response, new_call_cq, notification_cq, tag);
    }
  };
  template <class BaseClass>
  class WithRawMethod_VoidMethod : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(const Service* /*service*/) {}
   public:
    WithRawMethod_VoidMethod() {
      ::grpc::Service::MarkMethodRaw(1);
    }
    ~WithRawMethod_VoidMethod() override {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable synchronous version of this method
    ::grpc::Status VoidMethod(::grpc::ServerContext* /*context*/, const ::orderservice::Void* /*request*/, ::orderservice::Void* /*response*/) override {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
    void RequestVoidMethod(::grpc::ServerContext* context, ::grpc::ByteBuffer* request, ::grpc::ServerAsyncResponseWriter< ::grpc::ByteBuffer>* response, ::grpc::CompletionQueue* new_call_cq, ::grpc::ServerCompletionQueue* notification_cq, void *tag) {
      ::grpc::Service::RequestAsyncUnary(1, context, request, response, new_call_cq, notification_cq, tag);
    }
  };
  template <class BaseClass>
  class WithRawCallbackMethod_Order : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(const Service* /*service*/) {}
   public:
    WithRawCallbackMethod_Order() {
      ::grpc::Service::MarkMethodRawCallback(0,
          new ::grpc::internal::CallbackUnaryHandler< ::grpc::ByteBuffer, ::grpc::ByteBuffer>(
            [this](
                   ::grpc::CallbackServerContext* context, const ::grpc::ByteBuffer* request, ::grpc::ByteBuffer* response) { return this->Order(context, request, response); }));
    }
    ~WithRawCallbackMethod_Order() override {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable synchronous version of this method
    ::grpc::Status Order(::grpc::ServerContext* /*context*/, const ::orderservice::OrderRequest* /*request*/, ::orderservice::OrderResult* /*response*/) override {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
    virtual ::grpc::ServerUnaryReactor* Order(
      ::grpc::CallbackServerContext* /*context*/, const ::grpc::ByteBuffer* /*request*/, ::grpc::ByteBuffer* /*response*/)  { return nullptr; }
  };
  template <class BaseClass>
  class WithRawCallbackMethod_VoidMethod : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(const Service* /*service*/) {}
   public:
    WithRawCallbackMethod_VoidMethod() {
      ::grpc::Service::MarkMethodRawCallback(1,
          new ::grpc::internal::CallbackUnaryHandler< ::grpc::ByteBuffer, ::grpc::ByteBuffer>(
            [this](
                   ::grpc::CallbackServerContext* context, const ::grpc::ByteBuffer* request, ::grpc::ByteBuffer* response) { return this->VoidMethod(context, request, response); }));
    }
    ~WithRawCallbackMethod_VoidMethod() override {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable synchronous version of this method
    ::grpc::Status VoidMethod(::grpc::ServerContext* /*context*/, const ::orderservice::Void* /*request*/, ::orderservice::Void* /*response*/) override {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
    virtual ::grpc::ServerUnaryReactor* VoidMethod(
      ::grpc::CallbackServerContext* /*context*/, const ::grpc::ByteBuffer* /*request*/, ::grpc::ByteBuffer* /*response*/)  { return nullptr; }
  };
  template <class BaseClass>
  class WithStreamedUnaryMethod_Order : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(const Service* /*service*/) {}
   public:
    WithStreamedUnaryMethod_Order() {
      ::grpc::Service::MarkMethodStreamed(0,
        new ::grpc::internal::StreamedUnaryHandler<
          ::orderservice::OrderRequest, ::orderservice::OrderResult>(
            [this](::grpc::ServerContext* context,
                   ::grpc::ServerUnaryStreamer<
                     ::orderservice::OrderRequest, ::orderservice::OrderResult>* streamer) {
                       return this->StreamedOrder(context,
                         streamer);
                  }));
    }
    ~WithStreamedUnaryMethod_Order() override {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable regular version of this method
    ::grpc::Status Order(::grpc::ServerContext* /*context*/, const ::orderservice::OrderRequest* /*request*/, ::orderservice::OrderResult* /*response*/) override {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
    // replace default version of method with streamed unary
    virtual ::grpc::Status StreamedOrder(::grpc::ServerContext* context, ::grpc::ServerUnaryStreamer< ::orderservice::OrderRequest,::orderservice::OrderResult>* server_unary_streamer) = 0;
  };
  template <class BaseClass>
  class WithStreamedUnaryMethod_VoidMethod : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(const Service* /*service*/) {}
   public:
    WithStreamedUnaryMethod_VoidMethod() {
      ::grpc::Service::MarkMethodStreamed(1,
        new ::grpc::internal::StreamedUnaryHandler<
          ::orderservice::Void, ::orderservice::Void>(
            [this](::grpc::ServerContext* context,
                   ::grpc::ServerUnaryStreamer<
                     ::orderservice::Void, ::orderservice::Void>* streamer) {
                       return this->StreamedVoidMethod(context,
                         streamer);
                  }));
    }
    ~WithStreamedUnaryMethod_VoidMethod() override {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable regular version of this method
    ::grpc::Status VoidMethod(::grpc::ServerContext* /*context*/, const ::orderservice::Void* /*request*/, ::orderservice::Void* /*response*/) override {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
    // replace default version of method with streamed unary
    virtual ::grpc::Status StreamedVoidMethod(::grpc::ServerContext* context, ::grpc::ServerUnaryStreamer< ::orderservice::Void,::orderservice::Void>* server_unary_streamer) = 0;
  };
  typedef WithStreamedUnaryMethod_Order<WithStreamedUnaryMethod_VoidMethod<Service > > StreamedUnaryService;
  typedef Service SplitStreamedService;
  typedef WithStreamedUnaryMethod_Order<WithStreamedUnaryMethod_VoidMethod<Service > > StreamedService;
};

}  // namespace orderservice


#endif  // GRPC_order_5fservice_2eproto__INCLUDED

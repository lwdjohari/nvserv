#pragma once

#include <nvserv/components/component_config.h>
#include <nvserv/components/component_locator.h>
#include <nvserv/grpcl/grpcl.h>

#include "order_service.grpc.pb.h"
#include "order_service.pb.h"

namespace hello_world {

// class OrderServiceHandler
//                 : public nvserv::handlers::GrpcServiceHandler<
//                       orderservice::OrderRequest, orderservice::OrderResult>
//                       {
//  public:
//   using nvserv::handlers::GrpcServiceHandler<
//       orderservice::OrderRequest,
//       orderservice::OrderResult>::GrpcServiceHandler;

//  protected:
//   orderservice::OrderResult HandleOrder(
//       const orderservice::OrderRequest& request) const {
//     return orderservice::OrderResult();
//   }
//};

class OrderServiceImpl : public orderservice::OrderService::Service {
 public:
  explicit OrderServiceImpl(const nvserv::components::ComponentLocator& locator,
                        const nvserv::components::ComponentConfig& config) {}

  // Use the macro to define gRPC methods
  grpc::Status Order(grpc::ServerContext* context,
                     const orderservice::OrderRequest* request,
                     orderservice::OrderResult* response) override {
    return this
        ->HandleRequest<orderservice::OrderRequest, orderservice::OrderResult>(
            context, request, response, &OrderServiceImpl::HandleOrder);
  }

  grpc::Status VoidMethod(grpc::ServerContext* context,
                          const orderservice::Void* request,
                          orderservice::Void* response) override {
    return this->HandleRequest<orderservice::Void, orderservice::Void>(
        context, request, response, &OrderServiceImpl::HandleVoidMethod);
  }

 private:
  // cppcheck-suppress unknownMacro
  NV_GRPC_HANDLE_REQUEST_TEMPLATE()

  orderservice::OrderResult HandleOrder(
      const orderservice::OrderRequest& order_request) const {
    double total = 0.0;
    double discount = order_request.coupon().discount();

    for (const auto& product : order_request.products()) {
      total += product.quantity() * product.price();
    }

    double final_total = total - discount;

    orderservice::OrderResult response;
    response.set_total(total);
    response.set_discount(discount);
    response.set_final_total(final_total);

    return response;
  }

  orderservice::Void HandleVoidMethod(const orderservice::Void& request) const {
    // Business logic for void method
    std::cout << "VoidMethod called" << std::endl;
    return orderservice::Void();
  }
};
}  // namespace hello_world

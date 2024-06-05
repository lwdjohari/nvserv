#pragma once

#include <nvserv/grpcl/grpcl.h>

#include "order_service.grpc.pb.h"
#include "order_service.pb.h"

namespace hello_world {

class OrderServiceHandler : public orderservice::OrderService::Service {
 public:
  // Use the macro to define gRPC methods
  NV_GRPC_DEFINE_METHOD(OrderServiceHandler, Order, orderservice::OrderRequest,
                        orderservice::OrderResult)
  NV_GRPC_DEFINE_METHOD(OrderServiceHandler, VoidMethod, orderservice::Void,
                        orderservice::Void)

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
}  // namespace helloworld

#pragma once

// #include "nvserv/handlers/grpc_service_handler.h"
#include "nvserv/grpcl/grpcl.h"
#include "order_service.grpc.pb.h"
#include "order_service.pb.h"
namespace helloworld {

class OrderServiceHandler : public orderservice::OrderService::Service {
 public:
  // Use the macro to define gRPC methods
  grpc::Status Order(grpc::ServerContext* context,
                     const orderservice::OrderRequest* request,
                     orderservice::OrderResult* response) override {
    return this
        ->HandleRequest<orderservice::OrderRequest, orderservice::OrderResult>(
            context, request, response, &OrderServiceHandler::HandleOrder);
  }
  NV_GRPC_DEFINE_METHOD(OrderServiceHandler, VoidMethod, orderservice::Void,
                        orderservice::Void)

 private:
  template <typename Req, typename Res, typename Func>
  grpc::Status HandleRequest(grpc::ServerContext* context, const Req* request,
                             Res* response, Func func) const {
    Res resp = (this->*func)(*request);
    *response = resp;
    return grpc::Status::OK;
  }

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

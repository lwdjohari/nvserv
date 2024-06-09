#include <nvserv/components/component.h>
#include <nvserv/server/server.h>

#include "components/util_component.h"
#include "handlers/handlers.h"

int main(int argc, char* argv[]) {
  auto services = nvserv::server::CreateServerContext("hello-grpc");

  (*services.Components())
      .SetupServer("hello-world-grpc", nvserv::ServerType::Grpc, 9669)
      .RegisterComponent<hello_world::UtilComponent>("util-component")
      .RegisterGrpcServiceHandler<hello_world::OrderServiceImpl>();

  // return nvserv::server::RunServer("hello-world-grpc",std::move(services), argc, argv);

  return 0;
}
#include "components/util_component.h"
#include "handlers/handlers.h"
#include "nvserv/components/component_config.h"
#include "nvserv/components/component_list.h"
#include "nvserv/components/component_locator.h"
// #include "nvserv/http/http_server.h"
#include "nvserv/server/server.h"

int main(int argc, char* argv[]) {
  auto context = nvserv::server::CreateServerContext("hello-world-rest");
  auto components = context.Components();

  (*components)
      // .RegisterLogger("Hello-World-Rest")
      .RegisterComponent<hello_world::UtilComponent>("util-component");

  // auto log = std::dynamic_pointer_cast<nvserv::logs::Logging>(
  //     context.ComponentResolver()->Resolve("logging-component"));

  
  //   log->LogInfo("NvServ | Server Starting");
  //   log->LogTrace("Should be invisible");
  //   log->LogDebug("NvServ Debug Mode, should be invisible");

  //   log->LogWarning("Experimental, not for use in production yet!");

    
//    nvserv::server::RunServer("hello-world-grpc",std::move(services), argc,
//    argv);

  return 0;
}
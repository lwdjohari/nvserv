#include "components/util_component.h"
#include "handlers/handlers.h"
#include "nvserv/components/component_config.h"
#include "nvserv/components/component_list.h"
#include "nvserv/components/component_locator.h"
#include "nvserv/handlers/http_json_handler.h"
#include "nvserv/http/http_server.h"
#include "nvserv/server/server.h"

int main(int argc, char* argv[]) {
  auto locator = nvserv::components::ComponentLocator();
  auto config = nvserv::components::ComponentConfig();
  auto log = nvserv::logs::Logging(locator, config);

  log.Initialize("Hello-World-Rest")
      .AddDefaultConsoleLogger(nvserv::logs::LogLevel::Debug)
      .AddFileLogger(nvserv::logs::LogLevel::Info, "hello-world.log")
      .RegisterAll();

  log.LogInfo("NvServ | Server Starting");
  log.LogTrace("Should be invisible");
  log.LogDebug("NvServ Debug Mode, should be invisible");

  auto services =
      nvserv::components::ComponentList()
          .SetupServer("hello-world-rest", nvserv::ServerType::Http2Auto, 9669)
          .RegisterComponent<hello_world::UtilComponent>("util-component")
          .RegisterHttpHandler<helloworld::HelloWorldHandler>("api/v1/hello")
          .RegisterHttpHandler<helloworld::HelloWorldHandler>(
              "api/v1/hello/{greeting}");

  log.LogWarning("Experimental, not for use in production yet!");
  return nvserv::server::RunServer(services, argc, argv);
}
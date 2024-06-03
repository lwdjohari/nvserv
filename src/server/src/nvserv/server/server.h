#include "nvm/macro.h"
#include "nvserv/declare.h"
#include "nvserv/components/component.h"
#if NVSERV_SERVER_REST
#include "nvserv/server/http_server.h"
#endif
#include "nvserv/server/worker_config.h"

NVREST_BEGIN_NAMESPACE(server)

inline int RunServer(components::ComponentList& components, int argc,
                     char* argv[]) {
  return 0;
}

inline int RunServer(components::ComponentList& components) {
  return RunServer(components, 0, nullptr);
}
NVREST_END_NAMESPACE
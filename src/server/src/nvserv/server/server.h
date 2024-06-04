#include "nvm/macro.h"
#include "nvserv/components/component_list.h"
#include "nvserv/declare.h"

#include "nvserv/global_macro.h"
#include "nvserv/server/worker_config.h"

#if NVSERV_SERVER_REST == 1
#include "nvserv/http/http_server.h"
#endif

#if NVSERV_SERVER_GRPC == 1
#include "nvserv/server/grpc_server.h"
#endif

// cppcheck-suppress unknownMacro
NVREST_BEGIN_NAMESPACE(server)

inline int RunServer(components::ComponentList& components, int argc,
                     char* argv[]) {
  return 0;
}

inline int RunServer(components::ComponentList& components) {
  return RunServer(components, 0, nullptr);
}
NVREST_END_NAMESPACE
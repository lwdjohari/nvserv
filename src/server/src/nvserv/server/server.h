#include "nvm/macro.h"
#include "nvserv/components/component.h"
#include "nvserv/components/component_list.h"
#include "nvserv/declare.h"
#include "nvserv/global_macro.h"
#include "nvserv/server/main_execution_context.h"
#include "nvserv/server/server_base.h"
#include "nvserv/server/worker_config.h"

#if NVSERV_SERVER_REST == 1
#include "nvserv/http/http_server.h"
#endif

#if NVSERV_SERVER_GRPC == 1
#include "nvserv/server/grpc_server.h"
#endif

// cppcheck-suppress unknownMacro
NVREST_BEGIN_NAMESPACE(server)

inline MainExecutionContext& CreateServerContext(const std::string& name,
                                                 int argc, char* argv[]) {
  MainExecutionContext::CreateContext(name);
  return MainExecutionContext::Context();
}

inline MainExecutionContext& CreateServerContext(const std::string& name) {
  return CreateServerContext(name, 0, nullptr);
}
NVREST_END_NAMESPACE
#include "nvserv/server/main_execution_context.h"

NVREST_BEGIN_NAMESPACE(server)

// Define the static members
MainExecutionContextPtr MainExecutionContext::g_main_context_ = nullptr;
absl::Mutex MainExecutionContext::g_context_mutex_;

NVREST_END_NAMESPACE
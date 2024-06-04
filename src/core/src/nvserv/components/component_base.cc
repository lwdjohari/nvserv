#include <nvserv/components/component_base.h>

// cppcheck-suppress unknownMacro
NVREST_BEGIN_NAMESPACE(components)

ComponentBase::ComponentBase(const components::ComponentLocator& locator,
                             const components::ComponentConfig& config,
                             ComponentType type, bool is_monitor)
                : component_type_(type){}



NVREST_END_NAMESPACE

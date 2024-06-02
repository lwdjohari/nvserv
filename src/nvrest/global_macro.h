#if __cplusplus >= 201703L
#define __NR_CPP17 1
#else
#define __NR_CPP14 1
#endif

#if __NR_CPP17
#define __NR_RETURN_MOVE(arg) arg
#else
#define __NR_RETURN_MOVE(arg) std::move(arg)
#endif

#define NVREST_NAMESPACE namespace nvm::nvrest
#define NVREST_BEGIN_NAMESPACE(arg) NVREST_NAMESPACE::arg{
#define NVREST_END_NAMESPACE }
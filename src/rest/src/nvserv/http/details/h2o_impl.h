#pragma once

#include <h2o.h>

#include <memory>

#include "nvserv/global_macro.h"

//cppcheck-suppress unknownMacro
NVREST_BEGIN_NAMESPACE(http::details)

static h2o_globalconf_t config;
static h2o_context_t ctx;
static h2o_accept_ctx_t accept_ctx;

struct H2oServer {
  h2o_globalconf_t* config;
  h2o_context_t* context;
  h2o_accept_ctx_t* accept_context;
  h2o_hostconf_t* host_config;

  H2oServer()
                  : config(nullptr),
                    context(nullptr),
                    accept_context(nullptr),
                    host_config(nullptr){};

  bool IsServerCreated() const {
    return context;
  }
};

using H2oServerPtr = std::shared_ptr<H2oServer>;

inline H2oServerPtr CreateH2oServer(const std::string& host, int port) {
  auto h2o = std::make_shared<H2oServer>();
  h2o_config_init(&config);

  h2o->config = &config;
  h2o->context = &ctx;
  h2o->accept_context = &accept_ctx;
  h2o->host_config = h2o_config_register_host(
      &config, h2o_iovec_init(host.c_str(), host.size()), port);

  return __NR_RETURN_MOVE(h2o);
}

inline bool StartH2oServer(H2oServerPtr ptr) {
  if (!ptr)
    return false;

  return true;
  // struct sockaddr_in addr;
  // memset(&addr, 0, sizeof(addr));
  // addr.sin_family = AF_INET;
  // addr.sin_addr.s_addr = htonl(INADDR_ANY);
  // addr.sin_port = htons(8080);

  // http_sock_ =
  //     h2o_evloop_socket_create(ctx_.loop, (struct sockaddr*)&addr,
  //     sizeof(addr),
  //                              H2O_SOCKET_FLAG_DONT_READ);
  // h2o_accept_setup(http_sock_, &accept_ctx_);

  // if (https_enabled_) {
  //   addr.sin_port = htons(8443);
  //   https_sock_ =
  //       h2o_evloop_socket_create(ctx_.loop, (struct sockaddr*)&addr,
  //                                sizeof(addr), H2O_SOCKET_FLAG_DONT_READ);
  //   h2o_accept_setup(https_sock_, &accept_ctx_);
}

inline bool StopH2oServer(H2oServerPtr ptr) {
  if (!ptr)
    return false;

  return true;

  // if (http_sock_) {
  //   h2o_socket_close(http_sock_);
  //   http_sock_ = nullptr;
  // }
  // if (https_sock_) {
  //   h2o_socket_close(https_sock_);
  //   https_sock_ = nullptr;
  // }
}

bool RunH2o(H2oServerPtr ptr){
  if(!ptr)
  return false;

  return true;

  // while (h2o_evloop_run(ctx_.loop, 10) == 0) {
  // }
}
void EnableH2oHttps(H2oServerPtr ptr, const std::string& cert_file,
                    const std::string& key_file) {
  if (!ptr)
    return;
  // h2o_ssl_context_t* ssl_ctx = h2o_ssl_new_server_context(
  //     NULL, NULL, cert_file.c_str(), key_file.c_str(), NULL);
  // h2o_socket_ssl_set(ctx_.loop, https_sock_, ssl_ctx);
}

inline bool DisposeH2oServer(H2oServerPtr ptr) {
  if (!ptr)
    return false;

  if (ptr->IsServerCreated())
    h2o_context_dispose(ptr->context);
  if (!ptr->host_config)
    h2o_config_dispose(ptr->config);
  ptr->host_config = nullptr;

  return true;
}

NVREST_END_NAMESPACE

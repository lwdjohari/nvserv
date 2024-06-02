#pragma once

#include <h2o.h>

#include <cstdlib>
#include <cstring>
#include <iostream>
#include <memory>
#include <string>
#include <thread>
#include <vector>

#include "nvm/macro.h"
#include "nvrest/global.h"
#include "nvrest/server/declare.h"
#include "nvrest/server/details/h2o_impl.h"

//cppcheck-suppress unknownMacro
NVREST_BEGIN_NAMESPACE(server)

enum class HttpVersion {
  Http2,    // Use only HTTP/2
  Http1_1,  // Use HTTP/1.1 with fallback to HTTP/1.0
  Auto      // Auto fallback to HTTP/1.1 and HTTP/1.0 depending on client
};

NVM_ENUM_CLASS_DISPLAY_TRAIT(HttpVersion)

class HttpServer : public std::enable_shared_from_this<HttpServer> {
 public:
  explicit HttpServer(HttpVersion version, const std::string& host = "default",
                      int port = 8080, int num_threads = 4);

  ~HttpServer();

  void Start();
  void Stop();

  void EnableHttps(const std::string& cert_file, const std::string& key_file);
  void SetRequestHandler();
  HttpServerPtr Share();

 private:
  void Run();  // Worker thread function
  void SetupProtocol();

//   h2o_globalconf_t config_;
//   h2o_context_t ctx_;
//   h2o_hostconf_t* hostconf_;
//   h2o_pathconf_t* pathconf_;
//   h2o_accept_ctx_t accept_ctx_;
//   h2o_socket_t* http_sock_;
//   h2o_socket_t* https_sock_;
  details::H2oServerPtr server_;
  bool https_enabled_;
  int num_threads_;
  HttpVersion version_;
  std::vector<std::thread> workers_;  // Vector of worker threads
};

NVREST_END_NAMESPACE

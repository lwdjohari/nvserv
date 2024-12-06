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
#include <nvserv/global.h>
#include <nvserv/http/declare.h>
// #include <nvserv/http/details/h2o_impl.h>



//cppcheck-suppress unknownMacro
NVSERV_BEGIN_NAMESPACE(http)

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


  bool https_enabled_;
  int num_threads_;
  HttpVersion version_;
  std::vector<std::thread> workers_;  // Vector of worker threads
};

NVSERV_END_NAMESPACE

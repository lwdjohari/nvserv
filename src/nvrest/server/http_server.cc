#include "nvrest/server/http_server.h"

#include "http_server.h"

//cppcheck-suppress unknownMacro
NVREST_BEGIN_NAMESPACE(server)

HttpServer::HttpServer(HttpVersion version, const std::string& host, int port,
                       int num_threads)
                : server_(details::CreateH2oServer(host, port)),
                  https_enabled_(false),
                  num_threads_(num_threads),
                  version_(version) {
  if (!server_ || !server_->IsServerCreated()) {
    throw std::runtime_error("Can't create server on " + host + ":" +
                             std::to_string(port));
  }

  SetRequestHandler();
  SetupProtocol();
}

HttpServer::~HttpServer() {
  Stop();
  details::DisposeH2oServer(server_);
}

void HttpServer::Start() {
  auto state = details::StartH2oServer(server_);
  if (!state)
    throw std::runtime_error("Can not starting the server");

  // // Create worker threads
  // for (int i = 0; i < num_threads_; ++i) {
  //   workers_.emplace_back([self = shared_from_this()]() { self->Run(); });
  // }

  // // Wait for worker threads to finish
  // for (auto& worker : workers_) {
  //   worker.join();
  // }
}

void HttpServer::Stop() {
  details::StopH2oServer(server_);
}

void HttpServer::EnableHttps(const std::string& cert_file,
                             const std::string& key_file) {
  details::EnableH2oHttps(server_,cert_file,key_file);
  https_enabled_ = true;
}

#if __NR_CPP17
void HttpServer::SetRequestHandler() {
  // h2o_handler_t handler = h2o_create_handler(pathconf_, sizeof(handler));
  // handler->on_req = [](h2o_handler_t* self, h2o_req_t* req) -> int {
  //   h2o_send(req, H2O_STRLIT("Hello, World!"), H2O_SEND_STATE_FINAL);
  //   return 0;
  // };
}
#else
void HttpServer::setRequestHandler() {
  auto on_req = [](h2o_handler_t* self, h2o_req_t* req) -> int {
    h2o_send(req, H2O_STRLIT("Hello, World!"), H2O_SEND_STATE_FINAL);
    return 0;
  };

  h2o_handler_t* handler =
      (h2o_handler_t*)h2o_create_handler(pathconf_, sizeof(*handler));
  handler->on_req = on_req;
}
#endif

HttpServerPtr HttpServer::Share() {
  return shared_from_this();
}

void HttpServer::Run() {
  details::RunH2o(server_);
}

void HttpServer::SetupProtocol() {
  // switch (version_) {
  //   case HttpVersion::Http2:
  //     h2o_config_init_h2o_http2_only(&config_);
  //     break;
  //   case HttpVersion::Http1_1:
  //     h2o_config_init_h2o_http1_1_only(&config_);
  //     break;
  //   case HttpVersion::Auto:
  //     h2o_config_init_h2o_auto(&config_);
  //     break;
  // }
}

NVREST_END_NAMESPACE

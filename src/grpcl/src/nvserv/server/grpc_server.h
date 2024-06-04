#pragma once

#include <grpcpp/grpcpp.h>
#include <grpc/grpc.h>
#include <nvserv/global_macro.h>

#include <iostream>
#include <memory>

#include "nvserv/components/component_base.h"
#include "nvserv/components/component_config.h"
#include "nvserv/components/component_locator.h"
#include "nvserv/server/server_base.h"
// cppcheck-supress unknownMacro

NVREST_BEGIN_NAMESPACE(server)

class GrpcServer final : public ServerBase {
 public:
  static __NR_CONSTEXPR components::ComponentType kComponentType =
      components::ComponentType::kServerGrpc;

  explicit GrpcServer(components::ComponentLocator& locator,
                      components::ComponentConfig& config)
                  : ServerBase(locator, config, GrpcServer::kComponentType),
                    server_(),
                    builder_(),
                    creds_(),
                    addr_uri_(),
                    port_(){};

  void AddListeningPort(const std::string& addr_uri,
                        std::shared_ptr<grpc::ServerCredentials> creds,
                        int selected_port) {
    creds_ = creds == nullptr ? grpc::InsecureServerCredentials() : creds;
    addr_uri_ = std::string(addr_uri);
    port_ = selected_port;
    

  }

  ::grpc::ServerBuilder& CreateBuilder() {
    if (!builder_) {
      builder_ = std::make_unique<::grpc::ServerBuilder>();
      if (!addr_uri_.empty()) {
        builder_->AddListeningPort(addr_uri_, creds_, &port_);
      }
    }

    return *builder_;
  }

  void ResetBuilder() {
    builder_ = nullptr;
  }

  void Start() override {
    if (server_)
      throw std::runtime_error("Grpc Server already running");

    if (!builder_)
      throw std::invalid_argument("Null reference on builder_, call "
                                  "CreateBuilder before execute BuildServer()");
    server_ = std::move(builder_->BuildAndStart());

    if (!server_)
      throw std::runtime_error("Grpc server failed to start");
  };

  void Stop() override {
    if (!server_)
      return;
    server_->Shutdown(std::chrono::system_clock::now() + std::chrono::seconds(1));

  };

  void Wait() override {
    server_->Wait();
  };

  bool IsRun() const override {
    return server_ != nullptr;
  }

 private:
  std::unique_ptr<::grpc::Server> server_;
  std::unique_ptr<::grpc::ServerBuilder> builder_;
  std::shared_ptr<grpc::ServerCredentials> creds_;
  std::string addr_uri_;
  int port_;
};

NVREST_END_NAMESPACE
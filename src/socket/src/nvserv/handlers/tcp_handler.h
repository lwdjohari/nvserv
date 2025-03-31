#pragma once

#include <nvserv/global.h>
#include <nvserv/ssl/ssl.h>

#include <asio.hpp>
#include <asio/ssl.hpp>
#include <chrono>
#include <functional>
#include <iostream>
#include <memory>
#include <mutex>
#include <queue>
#include <thread>
#include <unordered_map>

using asio::ip::tcp;

NVSERV_BEGIN_NAMESPACE(ssl)

struct TcpServerConfig {
  bool non_blocking = true;
  size_t buffer_size = 4096;
  size_t max_connections_per_ip = 100;
  size_t rate_limit_per_ip = 10;  // Per second
  size_t max_user_connections = 5;
  bool enable_adaptive_control = true;
  bool ssl_is_use = false;
  std::string ssl_certificate_public_path = std::string();
  std::string ssl_certificate_private_path = std::string();
};

struct TcpSession {
  tcp::socket socket;
  std::array<char, 4096> buffer;
  std::chrono::steady_clock::time_point last_active;
  std::string ip;
  std::unique_ptr<asio::ssl::stream<tcp::socket>> ssl_socket;

  explicit TcpSession(asio::io_context& io_ctx, std::string client_ip,
                      asio::ssl::context& ssl_ctx, bool use_ssl)
                  : socket(io_ctx),
                    ip(std::move(client_ip)),
                    last_active(std::chrono::steady_clock::now()),
                    ssl_socket(nullptr) {
    if (use_ssl) {
      ssl_socket = std::make_unique<asio::ssl::stream<tcp::socket>>(
          std::move(socket), ssl_ctx);
    }
  }
};

class TcpServerHandler {
 public:
  TcpServerHandler(asio::io_context& io_context, uint16_t port,
                const TcpServerConfig& config);

  void StartAccept();
  void HandleClient(std::shared_ptr<TcpSession> session);
  bool CheckConnectionLimits(const std::string& ip);
  void OnReceive(std::shared_ptr<TcpSession> session, const char* data,
                 std::size_t length);
  void OnDisconnect(std::shared_ptr<TcpSession> session);

 private:
  asio::io_context& io_context_;
  tcp::acceptor acceptor_;
  TcpServerConfig config_;
  asio::ssl::context ssl_context_;
  std::unordered_map<std::string, std::queue<std::shared_ptr<TcpSession>>>
      clients_;
  std::unordered_map<std::string,
                     std::queue<std::chrono::steady_clock::time_point>>
      ip_connection_tracker_;
};

NVSERV_END_NAMESPACE

// int main() {
//   asio::io_context io_context;
//   TcpServerHandler::TcpServerConfig config;
//   config.use_ssl = true;
//   TcpServerHandler server(io_context, 8080, config);
//   io_context.run();
//   return 0;
// }

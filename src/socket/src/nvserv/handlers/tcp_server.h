#pragma once

#include <nvserv/global.h>
#include <nvserv/ssl/ssl.h>
#include <nvserv/handlers/tcp_declare.h>
#include <boost/asio.hpp>
#include <boost/asio/ssl.hpp>
#include <chrono>
#include <functional>
#include <iostream>
#include <memory>
#include <mutex>
#include <queue>
#include <thread>
#include <unordered_map>

NVSERV_BEGIN_NAMESPACE(handlers)

struct TcpServerConfig {
  bool keep_alive = true;
  bool tls_is_active = false;
  bool enable_rate_limiter = true;
  bool reuse_address = false;
  BufferType read_buffer_type = BufferType::STATIC;
  BufferFlushMethod read_flush_method = BufferFlushMethod::CALLBACK;
  BufferType write_buffer_type = BufferType::STATIC;
  BufferFlushMethod write_flush_method = BufferFlushMethod::CALLBACK;

  size_t read_buffer_max_size = 8192;
  size_t read_buffer_nodestream_chunk = 8192;
  size_t write_buffer_max_size = 8192;
  size_t write_buffer_nodestream_chunk = 8192;

  uint32_t read_buffer_nodestream_max_num_chunk = 40;
  uint32_t write_buffer_nodestream_max_num_chunk = 40;

  uint32_t read_timeout = 5000;   // ms
  uint32_t write_timeout = 5000;  // ms

  uint32_t idle_timeout = 30000;  // ms
  uint32_t rlimiter_max_connections = 0;
  uint32_t rlimiter_max_connection_per_second = 100;  // Per second
  uint32_t rlimiter_limit_per_ip_per_second = 100;    // Per second

  std::string tls_certificate_public_path = std::string();
  std::string tls_certificate_private_path = std::string();
};

class TcpContext {};

class TcpSession {
 public:
  explicit TcpSession(boost::asio::io_context& io_ctx, std::string client_ip,
                      boost::asio::ssl::context& ssl_ctx, bool use_ssl)
                  : _socket(io_ctx),
                    _ip(std::move(client_ip)),
                    _last_active(std::chrono::steady_clock::now()),
                    _ssl_socket(nullptr) {
    if (use_ssl) {
      _ssl_socket = std::make_unique<
          boost::asio::ssl::stream<boost::asio::ip::tcp::socket>>(
          std::move(socket), ssl_ctx);
    }
  }

 private:
  boost::asio::ip::tcp::socket _socket;
  std::array<char, 4096> _buffer;
  std::chrono::steady_clock::time_point _last_active;
  std::string _ip;
  std::unique_ptr<boost::asio::ssl::stream<boost::asio::ip::tcp::socket>>
      _ssl_socket;
};

class TcpServerHandler {
 public:
  TcpServerHandler(TcpServerConfig config);
  ~TcpServerHandler();

  void StartAccept();
  void HandleClient(std::shared_ptr<TcpSession> session);
  void OnReceive(std::shared_ptr<TcpSession> session, const char* data,
                 std::size_t length);
  void OnDisconnect(std::shared_ptr<TcpSession> session);

 private:
  std::shared_ptr<TcpContext> _context;
};

NVSERV_END_NAMESPACE
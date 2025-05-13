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
struct TcpClientConfig{
  bool keep_alive = true;
  bool tls_is_active = false;
  bool tls_is_use_public_cert = true;
  bool is_use_adaptive_retry = false;

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

  uint32_t connect_timeout = 10000; // ms
  uint32_t read_timeout = 5000;   // ms
  uint32_t write_timeout = 5000;  // ms
  uint32_t idle_timeout = 120000;  // ms
  
  std::string tls_certificate_public_path = std::string();
};

class TcpClientHandler{
  public:
    TcpClientHandler(TcpClientConfig config);
    ~TcpClientHandler();
};

NVSERV_END_NAMESPACE
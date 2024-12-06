#pragma once

#include "nvserv/http/declare.h"


NVSERV_BEGIN_NAMESPACE(http)

class Config {
 public:
  Config();

  void HttpVersion(HttpVersionMode version);
  void Compression(CompressionType type);
  void XssProtection(bool enable);
  void CsrfProtection(bool enable);
  void DosProtection(int rate_limit, int connection_limit);
  void Https(const std::string& cert_file, const std::string& key_file);
  void Cors(const std::string& allowed_origins);
  void Http1RequestTimeout(uint64_t timeout);
  void Http2IdleTimeout(uint64_t timeout);
  void Http2GracefulShutdownTimeout(uint64_t timeout);
  void Http2MaxConcurrentRequestsPerConnection(size_t max_conn);
  void Http2MaxStreamsForPriority(size_t max_stream);

  HttpVersionMode HttpVersion() const;
  CompressionType Compression() const;
  bool XssProtection() const;
  bool CsrfProtection() const;
  int RateLimit() const;
  int ConnectionLimit() const;
  std::string CertFile() const;
  std::string KeyFile() const;
  std::string Cors() const;
  uint64_t Http1RequestTimeout() const;
  uint64_t Http2IdleTimeout() const;
  uint64_t Http2GracefulShutdownTimeout() const;
  size_t Http2MaxConcurrentRequestsPerConnection() const;
  size_t Http2MaxStreamsForPriority() const;

 private:
  HttpVersionMode http_version_;
  CompressionType compression_;
  bool xss_protection_;
  bool csrf_protection_;
  int rate_limit_;
  int connection_limit_;
  std::string cert_file_;
  std::string key_file_;
  std::string cors_;
  uint64_t http1_request_timeout_;
  uint64_t http2_idle_timeout_;
  uint64_t http2_graceful_shutdown_timeout_;
  size_t http2_max_concurrent_requests_per_connection_;
  size_t http2_max_streams_for_priority_;
};


NVSERV_END_NAMESPACE
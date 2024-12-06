#include "nvserv/http/http_config.h"

NVSERV_BEGIN_NAMESPACE(http)

Config::Config()
                : http_version_(HttpVersionMode::HTTP2_AUTO_FALLBACK),
                  compression_(CompressionType::NONE),
                  xss_protection_(true),
                  csrf_protection_(false),
                  rate_limit_(0),
                  connection_limit_(0),
                  http1_request_timeout_(30),
                  http2_idle_timeout_(),
                  http2_graceful_shutdown_timeout_(),
                  http2_max_concurrent_requests_per_connection_(),
                  http2_max_streams_for_priority_() {}

void Config::HttpVersion(HttpVersionMode version) {
  http_version_ = version;
}

void Config::Compression(CompressionType type) {
  compression_ = type;
}

void Config::XssProtection(bool enable) {
  xss_protection_ = enable;
}

void Config::CsrfProtection(bool enable) {
  csrf_protection_ = enable;
}

void Config::DosProtection(int rate_limit, int connection_limit) {
  rate_limit_ = rate_limit;
  connection_limit_ = connection_limit;
}

void Config::Https(const std::string& cert_file, const std::string& key_file) {
  cert_file_ = cert_file;
  key_file_ = key_file;
}

void Config::Cors(const std::string& allowed_origins) {
  cors_ = allowed_origins;
}

void Config::Http1RequestTimeout(uint64_t timeout) {
  http1_request_timeout_ = timeout;
}
void Config::Http2IdleTimeout(uint64_t timeout) {
  http2_idle_timeout_ = timeout;
}
void Config::Http2GracefulShutdownTimeout(uint64_t timeout) {
  http2_graceful_shutdown_timeout_ = timeout;
}
void Config::Http2MaxConcurrentRequestsPerConnection(size_t max_conn) {
  http2_max_concurrent_requests_per_connection_ = max_conn;
}
void Config::Http2MaxStreamsForPriority(size_t max_stream) {
  http2_max_streams_for_priority_ = max_stream;
}

HttpVersionMode Config::HttpVersion() const {
  return http_version_;
}

CompressionType Config::Compression() const {
  return compression_;
}

bool Config::XssProtection() const {
  return xss_protection_;
}

bool Config::CsrfProtection() const {
  return csrf_protection_;
}

int Config::RateLimit() const {
  return rate_limit_;
}

int Config::ConnectionLimit() const {
  return connection_limit_;
}

std::string Config::CertFile() const {
  return cert_file_;
}

std::string Config::KeyFile() const {
  return key_file_;
}

std::string Config::Cors() const {
  return cors_;
}

uint64_t Config::Http1RequestTimeout() const {
  return http1_request_timeout_;
}

uint64_t Config::Http2IdleTimeout() const {
  return http2_idle_timeout_;
}

uint64_t Config::Http2GracefulShutdownTimeout() const {
  return http2_graceful_shutdown_timeout_;
}

size_t Config::Http2MaxConcurrentRequestsPerConnection() const {
  return http2_max_concurrent_requests_per_connection_;
}

size_t Config::Http2MaxStreamsForPriority() const {
  return http2_max_streams_for_priority_;
}

NVSERV_END_NAMESPACE
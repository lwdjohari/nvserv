#include "nvserv/handlers/tcp_handler.h"

NVSERV_BEGIN_NAMESPACE(handlers)

TcpServerHandler::TcpServerHandler(boost::asio::io_context& io_context, uint16_t port,
                                   const TcpServerConfig& config)
                : io_context_(io_context),
                  acceptor_(io_context, tcp::endpoint(tcp::v4(), port)),
                  config_(config),
                  ssl_context_(boost::asio::ssl::context::sslv23) {
  if (config_.ssl_is_use) {
    ssl_context_.set_options(boost::asio::ssl::context::default_workarounds |
                             boost::asio::ssl::context::no_sslv2 |
                             boost::asio::ssl::context::single_dh_use);
    ssl_context_.use_certificate_file(config_.ssl_certificate_public_path,
                                      boost::asio::ssl::context::pem);
    ssl_context_.use_private_key_file(config_.ssl_certificate_private_path,
                                      boost::asio::ssl::context::pem);
  }
  StartAccept();
}

void TcpServerHandler::StartAccept() {
  auto session = std::make_shared<TcpSession>(io_context_, "", ssl_context_,
                                              config_.ssl_is_use);
  acceptor_.async_accept(session->socket, [this, session](std::error_code ec) {
    if (!ec) {
      session->ip = session->socket.remote_endpoint().address().to_string();
      if (CheckConnectionLimits(session->ip)) {
        clients_[session->ip].push(session);
        if (config_.ssl_is_use) {
          session->ssl_socket->async_handshake(
              boost::asio::ssl::stream_base::server,
              [this, session](std::error_code ec) {
                if (!ec)
                  HandleClient(session);
                else
                  session->socket.close();
              });
        } else {
          HandleClient(session);
        }
      } else {
        session->socket.close();
      }
    }
    StartAccept();
  });
}

void TcpServerHandler::HandleClient(std::shared_ptr<TcpSession> session) {
  //auto self = shared_from_this();
  session->socket.async_read_some(
      boost::asio::buffer(session->buffer),
      [this, session](std::error_code ec, std::size_t length) {
        if (!ec) {
          session->last_active = std::chrono::steady_clock::now();
          OnReceive(session, session->buffer.data(), length);
          HandleClient(session);
        } else {
          clients_[session->ip].pop();
          session->socket.close();
          OnDisconnect(session);
        }
      });
}

bool TcpServerHandler::CheckConnectionLimits(const std::string& ip) {
  auto now = std::chrono::steady_clock::now();
  auto& ip_queue = ip_connection_tracker_[ip];

  while (!ip_queue.empty() &&
         std::chrono::duration_cast<std::chrono::seconds>(
             now - ip_queue.front()) >= std::chrono::seconds(1)) {
    ip_queue.pop();
  }

  if (clients_[ip].size() >= config_.max_connections_per_ip) {
    return false;
  }
  if (ip_queue.size() >= config_.rate_limit_per_ip) {
    return false;
  }
  ip_queue.push(now);
  return true;
}

void TcpServerHandler::OnReceive(std::shared_ptr<TcpSession> session,
                                 const char* data, std::size_t length) {
  std::cout << "Received from " << session->ip << ": "
            << std::string(data, length) << std::endl;
}

void TcpServerHandler::OnDisconnect(std::shared_ptr<TcpSession> session) {
  std::cout << "Disconnected: " << session->ip << std::endl;
}

NVSERV_END_NAMESPACE
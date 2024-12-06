#include "nvserv/http/http_request.h"

NVSERV_BEGIN_NAMESPACE(http)

// HttpRequest::HttpRequest(h2o_req_t* req) : req_(req) {
//   if (!req_) {
//     throw std::invalid_argument("Request object cannot be null");
//   }
// }

// std::string HttpRequest::GetPath() const {
//   return std::string(req_->path_normalized.base, req_->path_normalized.len);
// }

// std::string HttpRequest::Method() const {
//   return std::string(req_->method.base, req_->method.len);
// }

// std::unordered_map<std::string, std::string> HttpRequest::Headers() const {
//   std::unordered_map<std::string, std::string> headers;
//   for (size_t i = 0; i < req_->headers.size; ++i) {
//     const h2o_header_t& header = req_->headers.entries[i];
//     headers[std::string(header.name->base, header.name->len)] =
//         std::string(header.value.base, header.value.len);
//   }
//   return headers;
// }

// std::string HttpRequest::GetHeader(const std::string& name) const {
//   ssize_t header_index =
//       h2o_find_header_by_str(&req_->headers, name.c_str(), name.size(), -1);
//   if (header_index != -1) {
//     const h2o_header_t& header = req_->headers.entries[header_index];
//     return std::string(header.value.base, header.value.len);
//   }
//   return "";
// }

// std::string HttpRequest::GetBody() const {
//   return std::string(req_->entity.base, req_->entity.len);
// }

// std::string HttpRequest::GetQueryString(const std::string& name) const {
//   if (req_->query_at == SIZE_MAX) {
//     return "";
//   }

//   h2o_iovec_t query_string =
//       h2o_iovec_init(req_->path.base + req_->query_at + 1,
//                      req_->path.len - req_->query_at - 1);
//   size_t offset = h2o_strstr(query_string.base, query_string.len, name.c_str(),
//                              name.size());
//   if (offset == SIZE_MAX) {
//     return "";
//   }

//   const char* found = query_string.base + offset + name.size();
//   if (*found != '=') {
//     return "";
//   }
//   found++;

//   const char* end = (const char*)memchr(
//       found, '&', query_string.len - (found - query_string.base));
//   if (end == nullptr) {
//     end = query_string.base + query_string.len;
//   }

//   return std::string(found, end - found);
// }

NVSERV_END_NAMESPACE
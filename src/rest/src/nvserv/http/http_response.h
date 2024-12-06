#pragma once

#include <h2o.h>

#include <string>
#include <stdexcept>
#include "nvserv/global.h"
#include "nvserv/formats/json/value_builder.h"

NVSERV_BEGIN_NAMESPACE(http)

class HttpResponse {
 public:
  explicit HttpResponse(h2o_req_t* req);

  void Status(int status_code) const;
  void AddHeader(const std::string& name, const std::string& value) const;
  void Send(const std::string& body, int status_code = 200) const;
  void SendJson(const formats::json::JsonBuffer& json, int status_code = 200) const;

 private:
  h2o_req_t* req_;
};

NVSERV_END_NAMESPACE
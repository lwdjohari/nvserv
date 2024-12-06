#pragma once

#include "nvserv/components/component.h"
#include "nvserv/global_macro.h"
#include "nvserv/http/http_request.h"
#include "nvserv/http/http_response.h"

NVSERV_BEGIN_NAMESPACE(handlers)

class HttpHandlerBase : public components::Component {
 private:
 public:
  HttpHandlerBase(const components::ComponentLocator& locator,
                  const components::ComponentConfig& config,
                  components::ComponentType type
                  )
                  : Component(locator, config,type){};
  ~HttpHandlerBase(){};

 protected:
  virtual void ParseRequestData(const http::HttpRequestContext& context,
                                http::HttpRequest& request) const = 0;
};


class HandlerBase {
 public:
  virtual ~HandlerBase() = default;
  virtual void __HandleImpl(const http::HttpRequest& req,
                      const http::HttpResponse& res) const {
    throw std::runtime_error("Unimplemented void Handle on Handler base");
  };

  virtual void HandleRequest(
      const http::HttpRequest& req, const http::HttpResponse& res,
      const std::unordered_map<std::string, std::string>& params) const = 0;

//   static int HandlerCallback(h2o_handler_t* self, h2o_req_t* req) {
//     if (!self || !req)
//       return 1;

//     std::cout << "Callback received:"
//               << std::string(req->path_normalized.base,
//                              req->path_normalized.len)
//               << std::endl;

//     piconaut_handler_t* pico_handler = (piconaut_handler_t*)self;
//     HandlerBase* handler = static_cast<HandlerBase*>(pico_handler->handler);
//     http::Request request(req);
//     http::Response response(req);
//     handler->__HandleImpl(request, response);
//     return 0;
//   }
};

// inline h2o_handler_t* MakePiconautHandler(
//     h2o_pathconf_t* pathconf, std::shared_ptr<HandlerBase> handler) {
//   piconaut_handler_t* pico_handler;

//   pico_handler =
//       (piconaut_handler_t*)h2o_create_handler(pathconf, sizeof(*pico_handler));
//   // pico_handler->handler_context.on_context_init = on_context_init;
//   // pico_handler->handler_context.on_context_dispose = on_context_dispose;
//   pico_handler->handler_context.dispose = dispose;
//   pico_handler->handler_context.on_req = HandlerBase::HandlerCallback;
//   pico_handler->handler = static_cast<void*>(handler.get());
//   return &pico_handler->handler_context;
// }

NVSERV_END_NAMESPACE
#pragma once

#include <nvm/dates/datetime.h>
#include <nvserv/storages/postgres/pg_server.h>

namespace helloworld {
class HelloWorldTCPHandler {
 public:
  HelloWorldTCPHandler() {};

 private:
  nvserv::storages::postgres::PgServerPtr pg_;
};
}  // namespace helloworld

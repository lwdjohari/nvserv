#define CATCH_CONFIG_MAIN
#include <nvserv/route/router.h>

#include <cstdint>
#include <iostream>
#include <thread>
#include <unordered_map>

#include "catch2/catch_all.hpp"

void TestHandler(const std::unordered_map<std::string, std::string>& params) {
  std::cout << "Handler executed with params:\n";
  for (const auto& [key, value] : params) {
    std::cout << key << ": " << value << "\n";
  }
}

void WorkerAdd(nvserv::route::Router& router, const std::string& path) {
  try {
    router.AddRoute(path, TestHandler);
  } catch (const std::invalid_argument& e) {
    std::cout << "Invalid route pattern: " << path << std::endl;
  }
}

void WorkerMatch(const nvserv::route::Router& router, const std::string& path) {
  std::unordered_map<std::string, std::string> params;
  auto handler = router.MatchRoute(path, params);
  if (handler) {
    handler(params);
  } else {
    std::cout << "No matching route for path: " << path << std::endl;
  }
}

TEST_CASE("[Router] Router thread safety test", "[Router]") {
  nvserv::route::Router router;

  std::vector<std::thread> add_threads;
  std::vector<std::thread> match_threads;

  // Create threads to add routes
  add_threads.emplace_back(WorkerAdd, std::ref(router),
                           "/gallery/{gid}/photo/{pid}");
  add_threads.emplace_back(WorkerAdd, std::ref(router),
                           "/gallery/{gid}/photo/special");
  add_threads.emplace_back(WorkerAdd, std::ref(router),
                           "/gallery/{gid}/special");
  add_threads.emplace_back(WorkerAdd, std::ref(router), "/users/{uid}/profile");
  add_threads.emplace_back(WorkerAdd, std::ref(router),
                           "/posts/{pid}/comments/{cid}");
  add_threads.emplace_back(WorkerAdd, std::ref(router),
                           "/users/gallery/{gid}/photo/{pid}");

  for (auto& thread : add_threads) {
    thread.join();
  }

  // Create threads to match routes
  match_threads.emplace_back(WorkerMatch, std::cref(router),
                             "/gallery/123/photo/456");
  match_threads.emplace_back(WorkerMatch, std::cref(router),
                             "/gallery/789/photo/special");
  match_threads.emplace_back(WorkerMatch, std::cref(router),
                             "/users/42/profile");
  match_threads.emplace_back(WorkerMatch, std::cref(router),
                             "/posts/101/comments/202");
  match_threads.emplace_back(WorkerMatch, std::cref(router),
                             "/gallery/111/photo/222");
  match_threads.emplace_back(WorkerMatch, std::cref(router),
                             "/gallery/123/special");
  match_threads.emplace_back(WorkerMatch, std::cref(router),
                             "/users/gallery/256/photo/1024");

  for (auto& thread : match_threads) {
    thread.join();
  }

  // Ensure all routes matched correctly
  std::unordered_map<std::string, std::string> params;

  params.clear();
  REQUIRE(router.MatchRoute("/gallery/123/photo/456", params) != nullptr);
  REQUIRE(params["gid"] == "123");
  REQUIRE(params["pid"] == "456");

  params.clear();
  REQUIRE(router.MatchRoute("/gallery/789/photo/special", params) != nullptr);
  REQUIRE(params["gid"] == "789");
  if(params.find("pid")!= params.end()){
    std::cout << "ambiguity on:" << params["pid"] << std::endl;
  }

  params.clear();
  REQUIRE(router.MatchRoute("/users/42/profile", params) != nullptr);
  REQUIRE(params["uid"] == "42");

  params.clear();
  REQUIRE(router.MatchRoute("/posts/101/comments/202", params) != nullptr);
  REQUIRE(params["pid"] == "101");
  REQUIRE(params["cid"] == "202");

  params.clear();
  REQUIRE(router.MatchRoute("/gallery/111/photo/222", params) != nullptr);
  REQUIRE(params["gid"] == "111");
  REQUIRE(params["pid"] == "222");

  params.clear();
  REQUIRE(router.MatchRoute("/gallery/123/special", params) != nullptr);
  REQUIRE(params["gid"] == "123");

  params.clear();
  REQUIRE(router.MatchRoute("/users/gallery/256/photo/1024", params) != nullptr);
  REQUIRE(params["gid"] == "256");
  REQUIRE(params["pid"] == "1024");

  
}

TEST_CASE("[Router] Router handles basic dynamic route") {
  using Router = nvserv::route::Router;
  using HandlerFn = nvserv::route::Route::HandlerFn;

  Router router;

  // Define a simple handler for testing
  HandlerFn handler =
      [](const std::unordered_map<std::string, std::string>& params) {
        std::cout << "Handler executed with params:\n";
        for (const auto& [key, value] : params) {
          std::cout << key << ": " << value << "\n";
        }
      };

  router.AddRoute("/gallery/{gid}/photo/{pid}", handler);

  std::unordered_map<std::string, std::string> params;
  auto matched_handler = router.MatchRoute("/gallery/123/photo/456", params);
  REQUIRE(matched_handler != nullptr);
  REQUIRE(params["gid"] == "123");
  REQUIRE(params["pid"] == "456");
}

TEST_CASE("[Router] Router handles complex dynamic route with spaces removed") {
  using Router = nvserv::route::Router;
  using HandlerFn = nvserv::route::Route::HandlerFn;

  Router router;

  // Define a simple handler for testing
  HandlerFn handler =
      [](const std::unordered_map<std::string, std::string>& params) {
        std::cout << "Handler executed with params:\n";
        for (const auto& [key, value] : params) {
          std::cout << key << ": " << value << "\n";
        }
      };

  router.AddRoute("/gallery/{gid}/photo/{pid}", handler);

  std::unordered_map<std::string, std::string> params;
  auto matched_handler = router.MatchRoute("/gallery/123/photo/456", params);
  REQUIRE(matched_handler != nullptr);
  REQUIRE(params["gid"] == "123");
  REQUIRE(params["pid"] == "456");
}

TEST_CASE("[Router] Router differentiates between static and dynamic routes") {
  using Router = nvserv::route::Router;
  using HandlerFn = nvserv::route::Route::HandlerFn;

  Router router;

  // Define a simple handler for testing
  HandlerFn handler =
      [](const std::unordered_map<std::string, std::string>& params) {
        std::cout << "Handler executed with params:\n";
        for (const auto& [key, value] : params) {
          std::cout << key << ": " << value << "\n";
        }
      };

  // router.AddRoute("/gallery", handler);
  router.AddRoute("/gallery/{gid}/photo/special", handler);
  router.AddRoute("/gallery/{gid}/photo/{pid}", handler);
  router.AddRoute("/gallery/{gid}", handler);

  router.PrintRouterTree();
  std::unordered_map<std::string, std::string> params;

  // Test static route
  auto matched_handler = router.MatchRoute("/gallery", params);
  REQUIRE(matched_handler != nullptr);

  // Test dynamic route
  matched_handler = router.MatchRoute("/gallery/123", params);
  REQUIRE(matched_handler != nullptr);
  REQUIRE(params["gid"] == "123");
  REQUIRE(params.find("pid") == params.end());

  // Test dynamic route
  matched_handler = router.MatchRoute("/gallery/123/photo/456", params);
  REQUIRE(matched_handler != nullptr);
  REQUIRE(params["gid"] == "123");
  REQUIRE(params["pid"] == "456");
}

TEST_CASE("[Router] Router handles invalid route patterns") {
  using Router = nvserv::route::Router;
  using HandlerFn = nvserv::route::Route::HandlerFn;

  Router router;

  // Define a simple handler for testing
  HandlerFn handler =
      [](const std::unordered_map<std::string, std::string>& params) {
        std::cout << "Handler executed with params:\n";
        for (const auto& [key, value] : params) {
          std::cout << key << ": " << value << "\n";
        }
      };

  REQUIRE_THROWS_AS(router.AddRoute("/gallery/{gid}{pid}/photo", handler),
                    std::invalid_argument);
  REQUIRE_THROWS_AS(router.AddRoute("/gallery/{gid/photo", handler),
                    std::invalid_argument);
  REQUIRE_THROWS_AS(router.AddRoute("/gallery/gid}/photo", handler),
                    std::invalid_argument);
}


TEST_CASE("[Router] Print Router Tree") {
  using Router = nvserv::route::Router;
  using HandlerFn = nvserv::route::Route::HandlerFn;

  Router router;

  // Define a simple handler for testing
  HandlerFn handler =
      [](const std::unordered_map<std::string, std::string>& params) {
        std::cout << "Handler executed with params:\n";
        for (const auto& [key, value] : params) {
          std::cout << key << ": " << value << "\n";
        }
      };

  router.AddRoute("/home", handler);
  router.AddRoute("/users", handler);
  router.AddRoute("/users/{id}", handler);
  router.AddRoute("/users/{id}/profile", handler);
  router.AddRoute("/post", handler);
  router.AddRoute("/post/{period}/{id}/{slug}", handler);
  router.AddRoute("/post/new", handler);
  router.AddRoute("/post/edit/{id}", handler);
  router.AddRoute("/post/fave/{id}", handler);
  router.AddRoute("/gallery", handler);
  router.AddRoute("/gallery/{gid}/photo/special", handler);
  router.AddRoute("/gallery/{gid}/photo/{pid}", handler);
  router.AddRoute("/gallery/{gid}", handler);

  router.PrintRouterTree();
}
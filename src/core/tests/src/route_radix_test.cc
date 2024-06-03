#define CATCH_CONFIG_MAIN
#include <nvserv/route/router.h>

#include <cstdint>
#include <iostream>
#include <unordered_map>

#include "catch2/catch_all.hpp"


TEST_CASE("[Router] Router handles basic dynamic route") {
    using Router = nvserv::route::Router;
    using HandlerFn = nvserv::route::Route::HandlerFn;

    Router router;

    // Define a simple handler for testing
    HandlerFn handler = [](const std::unordered_map<std::string, std::string>& params) {
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
    HandlerFn handler = [](const std::unordered_map<std::string, std::string>& params) {
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
    HandlerFn handler = [](const std::unordered_map<std::string, std::string>& params) {
        std::cout << "Handler executed with params:\n";
        for (const auto& [key, value] : params) {
            std::cout << key << ": " << value << "\n";
        }
    };

    router.AddRoute("/gallery", handler);
    router.AddRoute("/gallery/{gid}/photo/special", handler);
    router.AddRoute("/gallery/{gid}/photo/{pid}", handler);
    router.AddRoute("/gallery/{gid}", handler);


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
    HandlerFn handler = [](const std::unordered_map<std::string, std::string>& params) {
        std::cout << "Handler executed with params:\n";
        for (const auto& [key, value] : params) {
            std::cout << key << ": " << value << "\n";
        }
    };

    REQUIRE_THROWS_AS(router.AddRoute("/gallery/{gid}{pid}/photo", handler), std::invalid_argument);
    REQUIRE_THROWS_AS(router.AddRoute("/gallery/{gid/photo", handler), std::invalid_argument);
    REQUIRE_THROWS_AS(router.AddRoute("/gallery/gid}/photo", handler), std::invalid_argument);
}
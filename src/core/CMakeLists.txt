cmake_minimum_required(VERSION 3.10)
project(nvserv CXX)

message(STATUS "NvServ Core: Configure")
message(STATUS "-----------------------")
#Main headers and sources
file(GLOB_RECURSE SOURCES_NVSERV_CORE CONFIGURE_DEPENDS
    ${CMAKE_CURRENT_SOURCE_DIR}/src/*.h
    ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/src/*.s
)



set(CORE_FEATURE_DEFINITION)
if(NVSERV_SERVER_REST)
    LIST(APPEND CORE_FEATURE_DEFINITION NVSERV_SERVER_REST=1)
endif()

if(NVSERV_SERVER_GRPC)
    LIST(APPEND CORE_FEATURE_DEFINITION NVSERV_SERVER_GRPC=1)
endif()

# Convert the list to a comma-separated string
string(JOIN ", " CORE_FEATURES_JOIN ${CORE_FEATURE_DEFINITION})

# Print the comma-separated list
message(STATUS "Compile Flags: ${CORE_FEATURES_JOIN}")

# nvserv::core
add_library(${PROJECT_NAME}_core STATIC ${SOURCES_NVSERV_CORE} )
target_link_libraries(${PROJECT_NAME}_core  
    PUBLIC
        nvcore 
        absl::base 
        absl::base 
        absl::flat_hash_map 
        absl::algorithm
        absl::numeric
        absl::random_random
        absl::synchronization 
        absl::strings
        absl::time
        absl::utility
        absl::status
        spdlog::spdlog
    )
set_target_properties(${PROJECT_NAME}_core PROPERTIES LINKER_LANGUAGE CXX)
target_compile_features(${PROJECT_NAME}_core PUBLIC ${CXX_FEATURE})
target_compile_definitions(${PROJECT_NAME}_core PRIVATE ${CORE_FEATURE_DEFINITION})

target_include_directories(${PROJECT_NAME}_core
    PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/src/
)

add_library(${PROJECT_NAME}::core ALIAS ${PROJECT_NAME}_core )

message(STATUS "Unit-Test nvserv::core: ${NVSERV_USE_TEST}")
if(NVSERV_USE_TEST)
    add_subdirectory(tests)
endif()  
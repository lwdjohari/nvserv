cmake_minimum_required(VERSION 3.10)
project(nvserv_hello_world_grpc CXX)

message(STATUS "NvServ - Hello World GRPC Example")
message(STATUS "-----------------------------")

if(NOT DEFINED NVSERV_CXX_VERSION)
    set(NVSERV_CXX_VERSION 17)
endif()
if(NOT DEFINED NVSERV_CXX_STANDARD_REQUIRED)
    set(NVSERV_CXX_STANDARD_REQUIRED ON)
endif()
if(NOT DEFINED NVSERV_CXX_EXTENSIONS)
    set(NVSERV_CXX_EXTENSIONS OFF)
endif()

include(ProjectCXX)
set(ISROOT FALSE)
NV_DETECT_IS_ROOT_PROJECT(ISROOT)
message(STATUS "NvRest Example Hello-world GRPC: ${ISROOT} ${NVSERV_CXX_VERSION}")

NV_PROPOGATE_CXX_OPTIONS(${NVSERV_CXX_VERSION} ${NVSERV_CXX_STANDARD_REQUIRED} ${NVSERV_CXX_EXTENSIONS})
set(CXX_FEATURE "")
NV_GET_CXX_STD_FEATURE(${NVSERV_CXX_VERSION} CXX_FEATURE)
message(STATUS "CXX Feature: ${CXX_FEATURE}")

# Find Protobuf and gRPC packages
find_package(Protobuf REQUIRED)
find_package(gRPC REQUIRED)
find_package(absl CONFIG REQUIRED)

# Ensure the gRPC plugin is found
if(NOT gRPC_CPP_PLUGIN_EXECUTABLE)
    find_program(gRPC_CPP_PLUGIN_EXECUTABLE NAMES grpc_cpp_plugin PATHS ${GRPC_BIN_DIR} ENV PATH NO_DEFAULT_PATH)
    if(NOT gRPC_CPP_PLUGIN_EXECUTABLE)
        message(FATAL_ERROR "gRPC C++ plugin not found. Please ensure it is installed and available in your PATH.")
    endif()
endif()

message(STATUS "Grpc plugin: ${gRPC_CPP_PLUGIN_EXECUTABLE}(${GRPC_BIN_DIR})")
# Set paths
set(PROTO_SRC_DIR "${CMAKE_CURRENT_SOURCE_DIR}/proto")
set(GENERATED_SRC_DIR "${CMAKE_CURRENT_SOURCE_DIR}/generated")

# Create a directory for the generated sources
file(MAKE_DIRECTORY ${GENERATED_SRC_DIR})

# Define the .proto files
set(PROTO_FILES "${PROTO_SRC_DIR}/order_service.proto")

# Define the custom commands to generate the C++ source and header files
foreach(PROTO_FILE ${PROTO_FILES})
    get_filename_component(PROTO_FILE_NAME ${PROTO_FILE} NAME_WE)
    message(STATUS "Compile proto: ${PROTO_FILE_NAME}")

    # Protobuf generation command
    set(PROTOBUF_CMD "${Protobuf_PROTOC_EXECUTABLE} --cpp_out=${GENERATED_SRC_DIR} -I ${PROTO_SRC_DIR} ${PROTO_FILE}")
    message(STATUS "Protobuf Command: ${PROTOBUF_CMD}")

    add_custom_command(
        OUTPUT ${GENERATED_SRC_DIR}/${PROTO_FILE_NAME}.pb.cc ${GENERATED_SRC_DIR}/${PROTO_FILE_NAME}.pb.h
        COMMAND ${Protobuf_PROTOC_EXECUTABLE}
        ARGS --cpp_out=${GENERATED_SRC_DIR} -I ${PROTO_SRC_DIR} ${PROTO_FILE}
        DEPENDS ${PROTO_FILE}
        COMMENT "Running protobuf compiler on ${PROTO_FILE}"
        VERBATIM
    )

    # gRPC generation command
    set(GRPC_CMD "${Protobuf_PROTOC_EXECUTABLE} --grpc_out=${GENERATED_SRC_DIR} --plugin=protoc-gen-grpc=${gRPC_CPP_PLUGIN_EXECUTABLE} -I ${PROTO_SRC_DIR} ${PROTO_FILE}")
    message(STATUS "gRPC Command: ${GRPC_CMD}")

    add_custom_command(
        OUTPUT ${GENERATED_SRC_DIR}/${PROTO_FILE_NAME}.grpc.pb.cc ${GENERATED_SRC_DIR}/${PROTO_FILE_NAME}.grpc.pb.h
        COMMAND ${Protobuf_PROTOC_EXECUTABLE}
        ARGS --grpc_out=${GENERATED_SRC_DIR} --plugin=protoc-gen-grpc=${gRPC_CPP_PLUGIN_EXECUTABLE} -I ${PROTO_SRC_DIR} ${PROTO_FILE}
        DEPENDS ${PROTO_FILE}
        COMMENT "Running gRPC compiler on ${PROTO_FILE}"
        VERBATIM
    )
endforeach()

# Collect all generated files
file(GLOB GENERATED_SRCS "${GENERATED_SRC_DIR}/*.cc")
file(GLOB GENERATED_HDRS "${GENERATED_SRC_DIR}/*.h")

# Ensure that generated files are produced before the main target
add_custom_target(generate_protos ALL DEPENDS ${GENERATED_SRCS} ${GENERATED_HDRS})

# Main headers and sources
file(GLOB_RECURSE NV_REST_EXAM2 CONFIGURE_DEPENDS
    ${CMAKE_CURRENT_SOURCE_DIR}/src/*.h
    ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/src/*.s
)

add_executable(${PROJECT_NAME} ${NV_REST_EXAM2} ${GENERATED_SRCS})
target_link_libraries(${PROJECT_NAME}
    PUBLIC
        nvserv::core
        nvserv::grpc
        nvserv::postgres
        nvserv::server
        ${GRPC_LIBRARIES} 
        absl::status
        absl::str_format
        absl::strings
        absl::base
        absl::time
)
set_target_properties(${PROJECT_NAME} PROPERTIES LINKER_LANGUAGE CXX)
target_compile_features(${PROJECT_NAME} PUBLIC ${CXX_FEATURE})

# add_dependencies(${PROJECT_NAME} generate_protos)

target_include_directories(${PROJECT_NAME}
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/src/
        ${GENERATED_SRC_DIR}
)

if(Sanitizers_FOUND)
    add_sanitizers("${PROJECT_NAME}")
    message(STATUS "${PROJECT_NAME}::ASAN:ON.")
endif()

message(STATUS "${PROJECT_NAME} Configuration Done!\n")

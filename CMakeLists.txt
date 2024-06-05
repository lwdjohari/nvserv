cmake_minimum_required(VERSION 3.10)
project(nvserv CXX)

message( STATUS "NvServ REST FRAMEWORK v1")
message( STATUS "-----------------------------")
set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake" ${CMAKE_MODULE_PATH})

# Main server development options
option(NVSERV_SERVER_REST  "Develop for server-side or REST API server" ON)
option(NVSERV_SERVER_GRPC "Develop for GRPC server" OFF)
option(NVSERV_SERVER_SOCKET "Develop for SOCKET (TCP/UDP) server" OFF)

# Storage feature
option(NVSERV_FEATURE_POSTGRES "Use NVSERV postgres datalayer" ON)
option(NVSERV_FEATURE_ORACLE "Use NVSERV oracle datalayer" OFF)
option(NVSERV_FEATURE_MYSQL "Use NVSERV mysql compatible datalayer" OFF)
option(NVSERV_FEATURE_SQLITE "Use NVSERV sqlite datalayer" OFF)
option(NVSERV_FEATURE_REDIS "Use NVSERV redis datalayer" OFF)
option(NVSERV_FEATURE_S3 "Use NVSERV S3 storage api" OFF)

# Network
option(NVSERV_FEATURE_ENVOY "Integrate Envoy Dataplane Library" OFF)

# Client
option(NVSERV_FEATURE_API_CLIENT "Http client for consuming web page or REST API" OFF)
option(NVSERV_FEATURE_GRPC_CLIENT "GRPC client for consuming GRPC Service" OFF)
option(NVSERV_FEATURE_MQTT_CLIENT "MQTT client for connecting to MQTT Service" OFF)
option(NVSERV_FEATURE_RABBITMQ_CLIENT "RABBIT MQ Client for connecting RABBIT MQ" OFF)

# VM
option(NVSERV_FEATURE_VM_V8 "Server Side V8 Javascript engine" OFF)

# LIBS
# Somehow when yout GRPC need specific ABSL Version
# You can override to set this to OFF and add your ABSL version
option(NVSERV_LIBS_ABSL_USE_BUNDLE "Use Abseil that is bundled with NvServ" ON)

# AVAILABLE ABSL 
# 202301251
# 202401161
if(NOT NVSERV_LIBS_ABSL_VERSION)
  set(NVSERV_LIBS_ABSL_VERSION 202301251)
endif()

if(NOT DEFINED NVSERV_LIBS_ABSL_USE_BUNDLE)
  set(NVSERV_LIBS_ABSL_USE_BUNDLE ON)
endif()

# Print the NVSERV FEATURES
message(STATUS "NVSERV FEATURES.")
message(STATUS "Core: ON")

if(NVSERV_SERVER_REST)
  message(STATUS "REST Server: ${NVSERV_SERVER_REST}")
endif()

if(NVSERV_SERVER_GRPC)
  message(STATUS "GRPC Server: ${NVSERV_SERVER_GRPC}")
endif()

if(NVSERV_SERVER_SOCKET)
  message(STATUS "SOCKET Server: ${NVSERV_SERVER_SOCKET}")
endif()

if(NVSERV_FEATURE_POSTGRES)
  message(STATUS "Postgres support: ${NVSERV_FEATURE_POSTGRES}")
endif()

if(NVSERV_FEATURE_API_CLIENT)
  message(STATUS "HTTP & API Client support: ${NVSERV_FEATURE_API_CLIENT}")
endif()


message(STATUS "")

message(STATUS "NvServ LIB DIR:${CMAKE_CURRENT_SOURCE_DIR}")

if(NOT NVSERV_CXX_VERSION)
    set(NVSERV_CXX_VERSION 17)
endif()
option(NVSERV_CXX_STANDARD_REQUIRED "CXX Required" ON)
option(NVSERV_CXX_EXTENSIONS "CXX Extensions" ON)

include(ProjectCXX)
set(ISROOT FALSE)
NV_DETECT_IS_ROOT_PROJECT(ISROOT)
message(STATUS "NvServ Root Project: ${ISROOT} ${NVSERV_CXX_VERSION}")

NV_PROPOGATE_CXX_OPTIONS(${NVSERV_CXX_VERSION} ${NVSERV_CXX_STANDARD_REQUIRED} ${NVSERV_CXX_EXTENSIONS})

set(CXX_FEATURE "")
NV_GET_CXX_STD_FEATURE(${NVSERV_CXX_VERSION} CXX_FEATURE)
message(STATUS "CXX Feature: ${CXX_FEATURE}")

set(ABSL_PROPAGATE_CXX_STD ON)

option(NVSERV_BUILD_DOC "Build documentation" OFF)
option(NVSERV_SANITIZE_ADDRESS "SANITIZE ADDRESS" ON)
option(NVSERV_USE_CATCH ON)
option(NVSERV_USE_TEST ON)
option(NVSERV_BUILD_EXAMPLE ON)

if(ISROOT)
  set(NVSERV_USE_CATCH ON)
  set(NVSERV_USE_TEST ON)
  set(NVSERV_BUILD_EXAMPLE ON)
  set(NVSERV_SERVER_GRPC ON)
  set(NVSERV_SERVER_REST ON)
  set(NVSERV_FEATURE_POSTGRES ON)

endif()

# Add ASAN
if(NVSERV_SANITIZE_ADDRESS)
    set(SANITIZE_ADDRESS ON)
endif(NVSERV_SANITIZE_ADDRESS)

#  make ourself sanitize and sane well.
if(NOT Sanitizers_FOUND)
 find_package(Sanitizers)
endif()

# Add Doxygen
if(NVSERV_BUILD_DOC)
    if(NOT DOXYGEN_FOUND)
        find_package(Doxygen)
    endif()

    if (DOXYGEN_FOUND)
        # set input and output files
        set(DOXYGEN_IN ${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile.in)
        set(DOXYGEN_OUT ${CMAKE_CURRENT_SOURCE_DIR}/generated/docs-cached/Doxyfile)

        # request to configure the file
        configure_file(${DOXYGEN_IN} ${DOXYGEN_OUT} @ONLY)
        message("Doxygen build started")

         # note the option ALL which allows to build the docs together with the application
        add_custom_target( doc_nvserv ALL
            COMMAND ${DOXYGEN_EXECUTABLE} ${DOXYGEN_OUT}
            WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/generated/docs-cached/
            COMMENT "Generating API documentation with Doxygen"
            VERBATIM )
    else (DOXYGEN_FOUND)
        message("Doxygen need to be installed to generate the doxygen documentation")
    endif (DOXYGEN_FOUND)
endif(NVSERV_BUILD_DOC)

# Add Unit Test Lib Catch2
if(NVSERV_USE_CATCH)
 message(STATUS  "CATCH2::ADD_LIB.")
 find_package(Catch2 3 REQUIRED)
endif()

find_package(Threads REQUIRED)

# Google Abseil
if(NVSERV_LIBS_ABSL_VERSION EQUAL 202301251  AND NVSERV_LIBS_ABSL_USE_BUNDLE)
  message(STATUS "Use Abseil Libs: ${NVSERV_LIBS_ABSL_VERSION}" )
  add_subdirectory(deps/abseil-lts20230125.1 build-abseil)
elseif(NVSERV_LIBS_ABSL_VERSION EQUAL 202401161 AND NVSERV_LIBS_ABSL_USE_BUNDLE)
  message(STATUS "Use Abseil Libs: ${NVSERV_LIBS_ABSL_VERSION}" )
  add_subdirectory(deps/abseil-lts20240116.1 build-abseil)
elseif(NVSERV_LIBS_ABSL_USE_BUNDLE)
  message(FATAL_ERROR "Not supported ABSEIL Version: ${NVSERV_LIBS_ABSL_VERSION}")
else()
  message("Use Abseil Libs: ABSEIL NOT USE FROM Bundle")
endif()


if (NOT nvcore_FOUND)
    add_subdirectory(deps/nvcore build-nvcore)
endif()

# if (NOT nvapi_FOUND)
#     add_subdirectory(deps/nvapi build-nvapi)
# endif()

#nvserv-core
add_subdirectory(src/core/ build-nvserv_core)

# nvserv::rest
if(NVSERV_SERVER_REST)
  add_subdirectory(src/rest/ build-nvserv_rest)
endif()

# nvserv::grpc
if(NVSERV_SERVER_GRPC)
find_package(Protobuf CONFIG REQUIRED)
find_package(gRPC CONFIG REQUIRED)

# Print the found versions
  if(Protobuf_FOUND)
      message(STATUS "Found Protobuf version ${Protobuf_VERSION}")
  else()
      message(FATAL_ERROR "Protobuf not found")
  endif()

  if(gRPC_FOUND)
      message(STATUS "Found gRPC version ${gRPC_VERSION}")
  else()
      message(FATAL_ERROR "gRPC not found")
  endif()

  SET(GRPC_LIBRARIES)
  LIST(APPEND GRPC_LIBRARIES 
    protobuf::libprotobuf
    gRPC::grpc
    gRPC::grpc++
    gRPC::grpc++_unsecure)

  add_subdirectory(src/grpcl/ build-nvserv_grpcl)
endif()

# nvserv::rest
if(NVSERV_FEATURE_POSTGRES)
  add_subdirectory(src/postgres/ build-nvserv_postgres)
endif()


# nvserv-server
# final server combine all needed linking
add_subdirectory(src/server/ build-nvserv_server)


# if(NVSERV_USE_TEST)
#     message(STATUS "TEST::ADD_UNIT_TEST.")
#     add_subdirectory(tests/nvserv)
# endif()       

message(STATUS "NvServ LIB Configuration Done!\n")
set(nvserv_FOUND  ON)

if(NVSERV_BUILD_EXAMPLE)
    add_subdirectory(examples/hello-world build-examples-hello-world)
    add_subdirectory(examples/hello-world-grpc build-examples-hello-world-grpc)
endif()

message(STATUS "")
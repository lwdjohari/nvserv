cmake_minimum_required(VERSION 3.10)
project(nvserv CXX)

message( STATUS "NvServ REST FRAMEWORK v1")
message( STATUS "-----------------------------")
set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake" ${CMAKE_MODULE_PATH})

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

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

option(NVSERV_LIB_NGHTTPX "Tell nghttp2 to use nvserv specific cmake, not the bundle one" ON)

# GRPC
# gRpc already have dependencies to Abseil, BoringSSL
# so when it use or not we need this dependencies from grpc
message(STATUS "Pull gRpc and it dependencies")
message(STATUS "NvServ needed dependencies of Abseil & BoringSSL from gRpc")

include(FetchContent)
set(FETCHCONTENT_BASE_DIR ${CMAKE_SOURCE_DIR}/third_party)

FetchContent_Declare(
  gRPC
  GIT_REPOSITORY https://github.com/grpc/grpc
  GIT_TAG        v1.54.2 # e.g v1.54.2 didn't error build
)
set(FETCHCONTENT_QUIET OFF)

set(ABSL_PROPAGATE_CXX_STD ON)

# Enable gRPC CMake options before `FetchContent_MakeAvailable`
# Disable unnecessary language support
set(gRPC_BUILD_TESTS OFF CACHE BOOL "" FORCE)        # Skip tests
set(gRPC_INSTALL OFF CACHE BOOL "" FORCE)           # Avoid global install
set(gRPC_BUILD_GRPC_CPP_PLUGIN ON CACHE BOOL "" FORCE)
set(gRPC_BUILD_CSHARP_EXT OFF CACHE BOOL "" FORCE)  # Disable C#
set(gRPC_BUILD_GRPC_CSHARP_PLUGIN OFF CACHE BOOL "" FORCE) # Skip C# plugin
set(gRPC_BUILD_GRPC_NODE_PLUGIN OFF CACHE BOOL "" FORCE)   # Skip Node.js
set(gRPC_BUILD_GRPC_OBJECTIVE_C_PLUGIN OFF CACHE BOOL "" FORCE) # Skip Obj-C
set(gRPC_BUILD_GRPC_PHP_PLUGIN OFF CACHE BOOL "" FORCE)    # Skip PHP
set(gRPC_BUILD_GRPC_PYTHON_PLUGIN OFF CACHE BOOL "" FORCE) # Skip Python
set(gRPC_BUILD_GRPC_RUBY_PLUGIN OFF CACHE BOOL "" FORCE)   # Skip Ruby

set(gRPC_CPP_PLUGIN_EXECUTABLE "${grpc_BINARY_DIR}/grpc_cpp_plugin")
set(Protobuf_PROTOC_EXECUTABLE "${protobuf_BINARY_DIR}/protoc")

# Use bundled dependencies for consistency
set(gRPC_USE_BUNDLED_PROTOBUF ON CACHE BOOL "" FORCE)
set(gRPC_USE_BUNDLED_ABSEIL ON CACHE BOOL "" FORCE)
get_property(GRPC_TARGETS GLOBAL PROPERTY TARGETS)

FetchContent_MakeAvailable(gRPC)

message(STATUS "gRPC source: ${grpc_SOURCE_DIR}")
message(STATUS "gRPC binary: ${grpc_BINARY_DIR}")
message(STATUS "gRPC-cpp plugin: ${gRPC_CPP_PLUGIN_EXECUTABLE}")

option(NVSERV_LIB_GRPC "" OFF)
option(NVSERV_LIB_GRPC_CPP "" OFF)
option(NVSERV_LIB_GRPC_CPP_UNSECURE "" OFF)
option(NVSERV_LIB_GRPC_CPP_REFLECTION "" OFF)
option(NVSERV_LIB_GRPC_CPP_PLUGIN_EXECUTABLE "" OFF)
option(NVSERV_LIB_GRPC_CPP_PROTOC_EXECUTABLE "" OFF)
option(NVSERV_LIB_GRPC_FOUND "" OFF)
option(NVSERV_LIB_GRPC_PLUGIN_FOUND "" OFF)
option(NVSERV_LIB_GRPC_GENERATOR_FOUND "" OFF)

set(NVSERV_LIB_GRPC OFF)
set(NVSERV_LIB_GRPC_CPP OFF)
set(NVSERV_LIB_GRPC_CPP_UNSECURE OFF)
set(NVSERV_LIB_GRPC_CPP_REFLECTION OFF)




if (TARGET grpc)
    message(STATUS "gRPC: gRPC lib OK")
    set(NVSERV_LIB_GRPC ON)
else()
    message(FATAL_ERROR "gRPC: Error gRPC  lib not found!")
endif()


if (TARGET grpc++)
    message(STATUS "gRPC: gRPC++ lib OK")
    set(NVSERV_LIB_GRPC_CPP ON )
else()
    message(FATAL_ERROR "gRPC: Error gRPC++ lib not found!")
endif()


if (TARGET grpc_unsecure)
    message(STATUS "gRPC: gRPC_unsecure lib OK")
    set(NVSERV_LIB_GRPC_CPP_UNSECURE ON )
else()
    message(FATAL_ERROR "gRPC: Error gRPC_unsecure lib not found!")
endif()

if (TARGET grpc++_reflection)
    message(STATUS "gRPC: gRPC++_reflection lib OK")
    set(NVSERV_LIB_GRPC_CPP_REFLECTION ON )
else()
    message(FATAL_ERROR "gRPC: Error gRPC_reflection lib not found!")
endif()



# For 1st time, protobuf protoc executable and grpc plugin is not build yet
# Create flags to create warning in the end, so the examples or project that is
# use Grpc not having chicken-egg problem during build
if(NOT Protobuf_PROTOC_EXECUTABLE OR NOT EXISTS ${Protobuf_PROTOC_EXECUTABLE})
    set(NVSERV_LIB_GRPC_CPP_PROTOC_EXECUTABLE OFF)
else()
    set(NVSERV_LIB_GRPC_CPP_PROTOC_EXECUTABLE ON)
endif()

if(NOT gRPC_CPP_PLUGIN_EXECUTABLE OR NOT EXISTS ${gRPC_CPP_PLUGIN_EXECUTABLE})
    set(NVSERV_LIB_GRPC_PLUGIN_FOUND OFF )
else()
    set(NVSERV_LIB_GRPC_PLUGIN_FOUND ON )
endif()

if(NVSERV_LIB_GRPC AND
    NVSERV_LIB_GRPC_CPP AND 
    NVSERV_LIB_GRPC_CPP_UNSECURE AND 
    NVSERV_LIB_GRPC_CPP_REFLECTION)
    set(NVSERV_LIB_GRPC_FOUND ON )
else()
    set(NVSERV_LIB_GRPC_FOUND OFF )
endif()

if(Protobuf_PROTOC_EXECUTABLE AND NVSERV_LIB_GRPC_PLUGIN_FOUND)
    set(NVSERV_LIB_GRPC_GENERATOR_FOUND ON )
else()
    set(NVSERV_LIB_GRPC_GENERATOR_FOUND OFF )
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
if (TARGET absl::base)
    message(STATUS "Use Abseil Libs: ABSEIL from gRpc deps")
    set(ABSL_PROPAGATE_CXX_STD ON)
else ()
    message(FATAL_ERROR "Use Abseil Libs: Error can not found ABSEIL ")
endif ()

if (NOT nvcore_FOUND)
    add_subdirectory(deps/nvcore build-nvcore)
endif()


#nvserv-core
add_subdirectory(deps/nvql/deps/nvserv-core/ build-nvserv_core)
add_subdirectory(deps/nvql build-nvql)

# nvserv::rest
if(NVSERV_SERVER_REST)
  add_subdirectory(src/rest/ build-nvserv_rest)
endif()

# nvserv::grpc
if(NVSERV_SERVER_GRPC)
 # gRpc quite large so we are use FetchContent
 # when the grpc is used, abseil and boringssl will be use 
 # from gRpc to avoid conflict

 # Print the found versions
  # Check protobuf version
  if (TARGET protobuf::libprotobuf)
    #get_target_property(PROTOBUF_VERSION protobuf::libprotobuf INTERFACE_COMPILE_DEFINITIONS)
    message(STATUS "Protobuf: ${PROTOBUF_VERSION}")
    # if (NOT PROTOBUF_VERSION VERSION_GREATER_EQUAL MIN_PROTOBUF_VERSION)
    #   message(FATAL_ERROR "Protobuf version ${PROTOBUF_VERSION} is less than required ${MIN_PROTOBUF_VERSION}")
    # endif()
    else()
    message(FATAL_ERROR "Protobuf: Protobuf not found")
  endif()
  
  message(STATUS "grpc: ${gRPC_VERSION}")
  message(STATUS "gRPC source: ${grpc_SOURCE_DIR}")
  message(STATUS "gRPC binary: ${grpc_BINARY_DIR}")


  if (TARGET grpc)
      message(STATUS "gRPC: gRPC lib OK")
  else()
      message(FATAL_ERROR "gRPC: Error gRPC  lib not found!")
  endif()


  if (TARGET grpc++)
      message(STATUS "gRPC: gRPC++ lib OK")
  else()
      message(FATAL_ERROR "gRPC: Error gRPC++ lib not found!")
  endif()


  if (TARGET grpc_unsecure)
      message(STATUS "gRPC: gRPC_unsecure lib OK")
  else()
      message(FATAL_ERROR "gRPC: Error gRPC_unsecure lib not found!")
  endif()

  if (TARGET grpc++_reflection)
      message(STATUS "gRPC: gRPC++_reflection lib OK")
  else()
      message(FATAL_ERROR "gRPC: Error gRPC_reflection lib not found!")
  endif()

  
  SET(GRPC_LIBRARIES)
  LIST(APPEND GRPC_LIBRARIES 
    protobuf::libprotobuf
    grpc
    grpc++
    grpc++_unsecure)

  
  add_subdirectory(src/grpcl/ build-nvserv_grpcl)

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
    if(NVSERV_SERVER_REST)
#     add_subdirectory(examples/hello-world build-examples-hello-world)
    endif()
    if(NVSERV_SERVER_GRPC)
        if(NVSERV_LIB_GRPC_GENERATOR_FOUND)
            add_subdirectory(examples/hello-world-grpc build-examples-hello-world-grpc)
        else()
            message(STATUS " GRPC LIB & PLUGIN NEED TO BUILD FIRST! 
    RUN BUILD!

    Please build NvServ first! 
    NvServ will build gRPC lib and 
    plugins generator needed!.
    Once has been built, you can build 
    your nvserv::grpc project.
  
    NOTES: 
    gRPC Plugins and Protobuf compiler 
    only being used during build, 
    WILL NOT INCLUDED IN NVSERV BUILD ARTIFACTS.")
        endif()
    endif()
endif()

message(STATUS "")
cmake_minimum_required(VERSION 3.10)
project(nvserv CXX)

message(STATUS "NvServ Server: Configure")
message(STATUS "-----------------------")

if(NVSERV_BUILD_LOCAL_SHARED)
    set(_LIBRARY_TYPE SHARED)
    set(CMAKE_POSITION_INDEPENDENT_CODE ON)
endif()

#Main headers and sources
file(GLOB_RECURSE SOURCES_NVSERV_SERVER CONFIGURE_DEPENDS
    ${CMAKE_CURRENT_SOURCE_DIR}/src/*.h
    ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/src/*.s
)

set(FEATURE_LIBS)
if(NVSERV_FEATURE_POSTGRES)
    LIST(APPEND FEATURE_LIBS nvserv::storage)
    LIST(APPEND FEATURE_LIBS nvserv::postgres)
endif()

# if(NVSERV_SERVER_REST)
#     LIST(APPEND FEATURE_LIBS nvserv::rest)
# endif()

if(NVSERV_SERVER_GRPC)
    LIST(APPEND FEATURE_LIBS nvserv::grpc)
    # LIST(APPEND FEATURE_LIBS ${GRPC_LIBRARIES})
endif()

if(NVSERV_SERVER_SOCKET)
    LIST(APPEND FEATURE_LIBS nvserv::socket)
endif()


set(FEATURE_DEFINITION)

if(NVSERV_FEATURE_POSTGRES)
    LIST(APPEND FEATURE_DEFINITION NVSERV_FEATURE_POSTGRES=1)
endif()

# if(NVSERV_SERVER_REST)
#     LIST(APPEND FEATURE_DEFINITION NVSERV_SERVER_REST=1)
# endif()

if(NVSERV_SERVER_GRPC)
    LIST(APPEND FEATURE_DEFINITION NVSERV_SERVER_GRPC=1)
endif()

if(NVSERV_SERVER_SOCKET)
    LIST(APPEND FEATURE_DEFINITION NVSERV_SERVER_SOCKET=1)
endif()

# Convert the list to a comma-separated string
string(JOIN ", " FEATURES_JOIN ${FEATURE_DEFINITION})

# Print the comma-separated list
message(STATUS "Compile Flags: ${FEATURES_JOIN}")

# target_compile_definitions(${PROJECT_NAME}_server PRIVATE ${FEATURE_DEFINITION})

# nvserv::server
add_library(${PROJECT_NAME}_server ${_LIBRARY_TYPE} ${SOURCES_NVSERV_SERVER} )
target_link_libraries(${PROJECT_NAME}_server  
    PUBLIC
        ${PROJECT_NAME}::core
        ${FEATURE_LIBS}
    )

# Set runtime path for the shared library
if(NVSERV_BUILD_LOCAL_SHARED)
    set_target_properties(${PROJECT_NAME}_server PROPERTIES
        LINKER_LANGUAGE CXX
        # BUILD_RPATH "$ORIGIN"                   # Use the directory of the binary
        # INSTALL_RPATH "$ORIGIN"                 # Set for installed binaries too
        # BUILD_WITH_INSTALL_RPATH TRUE           # Ensure RPATH is embedded during the build
        VERSION ${NVSERV_LIBRARY_VERSION}       # Semantic Version of library
        SOVERSION ${NVSERV_LIBRARY_SOVERSION}   # Linker version for sysmlink
    )
endif()

if(NVSERV_BUILD_STATIC)
    set_target_properties(${PROJECT_NAME}_server PROPERTIES
        LINKER_LANGUAGE CXX
    )
endif()
target_compile_features(${PROJECT_NAME}_server PUBLIC ${CXX_FEATURE})
target_compile_definitions(${PROJECT_NAME}_server PUBLIC ${FEATURE_DEFINITION})
target_include_directories(${PROJECT_NAME}_server
    PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/src/
)

add_library(${PROJECT_NAME}::server ALIAS ${PROJECT_NAME}_server )
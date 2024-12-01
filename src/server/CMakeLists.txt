cmake_minimum_required(VERSION 3.10)
project(nvserv CXX)

message(STATUS "NvServ Server: Configure")
message(STATUS "-----------------------")

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

# Convert the list to a comma-separated string
string(JOIN ", " FEATURES_JOIN ${FEATURE_DEFINITION})

# Print the comma-separated list
message(STATUS "Compile Flags: ${FEATURES_JOIN}")

# target_compile_definitions(${PROJECT_NAME}_server PRIVATE ${FEATURE_DEFINITION})

# nvserv::server
add_library(${PROJECT_NAME}_server STATIC ${SOURCES_NVSERV_SERVER} )
target_link_libraries(${PROJECT_NAME}_server  
    PUBLIC
        ${PROJECT_NAME}::core
        ${FEATURE_LIBS}
    )
set_target_properties(${PROJECT_NAME}_server PROPERTIES LINKER_LANGUAGE CXX)
target_compile_features(${PROJECT_NAME}_server PUBLIC ${CXX_FEATURE})
target_compile_definitions(${PROJECT_NAME}_server PUBLIC ${FEATURE_DEFINITION})
target_include_directories(${PROJECT_NAME}_server
    PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/src/
)

add_library(${PROJECT_NAME}::server ALIAS ${PROJECT_NAME}_server )
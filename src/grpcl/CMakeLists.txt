cmake_minimum_required(VERSION 3.10)
project(nvserv CXX)

message(STATUS "NvServ Grpc: Configure")
message(STATUS "-----------------------")

if(NVSERV_BUILD_LOCAL_SHARED)
    set(_LIBRARY_TYPE SHARED)
    set(CMAKE_POSITION_INDEPENDENT_CODE ON)
endif()

#Main headers and sources
file(GLOB_RECURSE SOURCES_NVSERV_GRPC CONFIGURE_DEPENDS
    ${CMAKE_CURRENT_SOURCE_DIR}/src/*.h
    ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/src/*.s
)


# Convert the list to a comma-separated string
string(JOIN ", " GRPC_LIB_JOIN ${GRPC_LIBRARIES})

# Print the comma-separated list
message(STATUS "Linking to: ${GRPC_LIB_JOIN}")

# nvserv::grpc
add_library(${PROJECT_NAME}_grpc ${_LIBRARY_TYPE} ${SOURCES_NVSERV_GRPC} )
target_link_libraries(${PROJECT_NAME}_grpc  
    PUBLIC
        nvserv::core
        ${GRPC_LIBRARIES} 
    )

# Set runtime path for the shared library
if(NVSERV_BUILD_LOCAL_SHARED)
    set_target_properties(${PROJECT_NAME}_grpc PROPERTIES
        LINKER_LANGUAGE CXX
        # BUILD_RPATH "$ORIGIN"                   # Use the directory of the binary
        # INSTALL_RPATH "$ORIGIN"                 # Set for installed binaries too
        # BUILD_WITH_INSTALL_RPATH TRUE           # Ensure RPATH is embedded during the build
        VERSION ${NVSERV_LIBRARY_VERSION}       # Semantic Version of library
        SOVERSION ${NVSERV_LIBRARY_SOVERSION}   # Linker version for sysmlink
    )
endif()

if(NVSERV_BUILD_STATIC)
    set_target_properties(${PROJECT_NAME}_grpc PROPERTIES
        LINKER_LANGUAGE CXX
    )
endif()

target_compile_features(${PROJECT_NAME}_grpc PUBLIC ${CXX_FEATURE})
target_include_directories(${PROJECT_NAME}_grpc
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/src/
)

add_library(${PROJECT_NAME}::grpc ALIAS ${PROJECT_NAME}_grpc )

# message(STATUS "Unit-Test nvserv::grpc: ${NVSERV_USE_TEST}")
# if(NVSERV_USE_TEST)
#     add_subdirectory(tests)
# endif()  
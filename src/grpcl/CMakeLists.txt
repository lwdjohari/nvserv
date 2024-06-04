cmake_minimum_required(VERSION 3.10)
project(nvserv CXX)

message(STATUS "NvServ Grpc: Configure")
message(STATUS "-----------------------")

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
add_library(${PROJECT_NAME}_grpc STATIC ${SOURCES_NVSERV_GRPC} )
target_link_libraries(${PROJECT_NAME}_grpc  
    PUBLIC
        nvserv::core
        ${GRPC_LIBRARIES} 
    )
set_target_properties(${PROJECT_NAME}_grpc PROPERTIES LINKER_LANGUAGE CXX)
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
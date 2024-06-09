cmake_minimum_required(VERSION 3.10)
project(nvserv_hello_world CXX)

message(STATUS "NvServ - Hello World Example")
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
message(STATUS "NvRest Example Hello-world: ${ISROOT} ${NVSERV_CXX_VERSION}")

NV_PROPOGATE_CXX_OPTIONS(${NVSERV_CXX_VERSION} ${NVSERV_CXX_STANDARD_REQUIRED} ${NVSERV_CXX_EXTENSIONS})
set(CXX_FEATURE "")
NV_GET_CXX_STD_FEATURE(${NVSERV_CXX_VERSION} CXX_FEATURE)
message(STATUS "CXX Feature: ${CXX_FEATURE}")

# Main headers and sources
file(GLOB_RECURSE NV_REST_EXAM1 CONFIGURE_DEPENDS
    ${CMAKE_CURRENT_SOURCE_DIR}/src/*.h
    ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/src/*.s
)


add_executable(${PROJECT_NAME} ${NV_REST_EXAM1})
target_link_libraries(${PROJECT_NAME}  
    PUBLIC
        nvserv::core
        nvserv::rest
        nvserv::postgres
        nvserv::server
    )
set_target_properties(${PROJECT_NAME} PROPERTIES LINKER_LANGUAGE CXX)
target_compile_features(${PROJECT_NAME} PUBLIC ${CXX_FEATURE})

target_include_directories(${PROJECT_NAME}
    PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/src/
)


# if(Sanitizers_FOUND)
#     add_sanitizers("${PROJECT_NAME}")
#     message(STATUS "${PROJECT_NAME}::ASAN:ON.")
# endif()
   

message(STATUS "${PROJECT_NAME} Configuration Done!\n")
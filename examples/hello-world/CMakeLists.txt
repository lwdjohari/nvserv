cmake_minimum_required(VERSION 3.10)
project(nvrest_hello_world CXX)

message(STATUS "NvREST - Hello World Example")
message(STATUS "-----------------------------")

if(NOT NVREST_CXX_VERSION)
    set(NVREST_CXX_VERSION 17)
endif()
if(NOT DEFINED NVREST_CXX_STANDARD_REQUIRED)
    set(NVREST_CXX_STANDARD_REQUIRED ON)
endif()
if(NOT DEFINED NVREST_CXX_EXTENSIONS)
    set(NVREST_CXX_EXTENSIONS OFF)
endif()

include(ProjectCXX)
set(ISROOT FALSE)
NV_DETECT_IS_ROOT_PROJECT(ISROOT)
message(STATUS "NvRest Example Hello-world: ${ISROOT} ${NVREST_CXX_VERSION}")

NV_PROPOGATE_CXX_OPTIONS(${NVREST_CXX_VERSION} ${NVREST_CXX_STANDARD_REQUIRED} ${NVREST_CXX_EXTENSIONS})

# Main headers and sources
file(GLOB_RECURSE NV_REST_EXAM1 CONFIGURE_DEPENDS
    ${CMAKE_CURRENT_SOURCE_DIR}/src/*.h
    ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/src/*.s
)


add_executable(${PROJECT_NAME} ${NV_REST_EXAM1})
target_link_libraries(${PROJECT_NAME}  
    nvcore 
    nvrest
    ${H2O_LIBRARIES}
    )
set_target_properties(${PROJECT_NAME} PROPERTIES LINKER_LANGUAGE CXX)
target_compile_features(${PROJECT_NAME} PUBLIC)

target_include_directories(${PROJECT_NAME}
    PUBLIC
        src/
        ${H2O_INCLUDE_DIRS}
)


if(Sanitizers_FOUND)
    add_sanitizers("${PROJECT_NAME}")
    message(STATUS "${PROJECT_NAME}::ASAN:ON.")
endif()
   

message(STATUS "${PROJECT_NAME} Configuration Done!\n")
cmake_minimum_required(VERSION 3.10)
project(nvrest CXX)

message( STATUS "NvREST REST FRAMEWORK v1")
message( STATUS "-----------------------------")
message(STATUS "NvREST LIB DIR:${CMAKE_CURRENT_SOURCE_DIR}")
set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake" ${CMAKE_MODULE_PATH})

if(NOT NVREST_CXX_VERSION)
    set(NVREST_CXX_VERSION 17)
endif()
option(NVREST_CXX_STANDARD_REQUIRED "CXX Required" ON)
option(NVREST_CXX_EXTENSIONS "CXX Extensions" ON)

include(ProjectCXX)
set(ISROOT FALSE)
NV_DETECT_IS_ROOT_PROJECT(ISROOT)
message(STATUS "NvRest Root Project: ${ISROOT} ${NVREST_CXX_VERSION}")

NV_PROPOGATE_CXX_OPTIONS(${NVREST_CXX_VERSION} ${NVREST_CXX_STANDARD_REQUIRED} ${NVREST_CXX_EXTENSIONS})

set(CXX_FEATURE "")
NV_GET_CXX_STD_FEATURE(${NVREST_CXX_VERSION} CXX_FEATURE)
message(STATUS "CXX Feature: ${CXX_FEATURE}")

set(ABSL_PROPAGATE_CXX_STD ON)

option(NV_REST_BUILD_DOC "Build documentation" OFF)
option(NV_REST_SANITIZE_ADDRESS "SANITIZE ADDRESS" ON)
option(NV_REST_USE_CATCH ON)
option(NV_REST_USE_LIB ON)
option(NV_REST_USE_TEST ON)
option(NV_REST_BUILD_EXAMPLE ON)


set(NV_REST_BUILD_DOC OFF)
set(NV_REST_SANITIZE_ADDRESS ON)
set(NV_REST_USE_CATCH ON)
set(NV_REST_USE_LIB ON)
set(NV_REST_USE_TEST OFF)
set(NV_REST_BUILD_EXAMPLE ON)


# Add ASAN
if(NV_REST_SANITIZE_ADDRESS)
    set(SANITIZE_ADDRESS ON)
endif(NV_REST_SANITIZE_ADDRESS)

#  make ourself sanitize and sane well.
if(NOT Sanitizers_FOUND)
 find_package(Sanitizers)
endif()

# Add Doxygen
if(NV_REST_BUILD_DOC)
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
        add_custom_target( doc_nvrest ALL
            COMMAND ${DOXYGEN_EXECUTABLE} ${DOXYGEN_OUT}
            WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/generated/docs-cached/
            COMMENT "Generating API documentation with Doxygen"
            VERBATIM )
    else (DOXYGEN_FOUND)
        message("Doxygen need to be installed to generate the doxygen documentation")
    endif (DOXYGEN_FOUND)
endif(NV_REST_BUILD_DOC)

# Add Unit Test Lib Catch2
if(NV_REST_USE_CATCH)
 message(STATUS  "CATCH2::ADD_LIB.")
 find_package(Catch2 3 REQUIRED)
endif()


# Add dependencies source code

# Include custom FindH2O module
find_package(Wslay REQUIRED)
if(NOT WSLAY_FOUND)
    message(FATAL_ERROR "wslay library not found")
endif()
find_package(H2O REQUIRED)


if (NOT nvcore_FOUND)
    add_subdirectory(deps/nvcore build-nvcore)
endif()

# if (NOT nvapi_FOUND)
#     add_subdirectory(deps/nvapi build-nvapi)
# endif()


# Main headers and sources
file(GLOB_RECURSE SOURCES_NV_REST CONFIGURE_DEPENDS
    ${CMAKE_CURRENT_SOURCE_DIR}/src/*.h
    ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/src/*.s
)


add_library(${PROJECT_NAME} STATIC ${SOURCES_NV_REST} )
target_link_libraries(${PROJECT_NAME}  
    nvcore 
    ${H2O_LIBRARIES}
    )
set_target_properties(${PROJECT_NAME} PROPERTIES LINKER_LANGUAGE CXX)
target_compile_features(${PROJECT_NAME} PUBLIC ${CXX_FEATURE})
target_include_directories(${PROJECT_NAME}
    PUBLIC
        src/
        ${H2O_INCLUDE_DIRS}
)


add_executable(${PROJECT_NAME}-test main.cc)
if(Sanitizers_FOUND)
    add_sanitizers("${PROJECT_NAME}-test")
    message(STATUS "${PROJECT_NAME}-test_LIB::ASAN:ON.")
endif()

target_link_libraries(${PROJECT_NAME}-test PRIVATE ${PROJECT_NAME} )
target_compile_features(${PROJECT_NAME}-test PUBLIC ${CXX_FEATURE})
target_include_directories("${PROJECT_NAME}-test"
    PUBLIC
        src/
)

if(NV_REST_USE_TEST)
    message(STATUS "TEST::ADD_UNIT_TEST.")
    add_subdirectory(tests/nvrest)
endif()       

message(STATUS "NvREST LIB Configuration Done!\n")
set(nvrest_FOUND  ON)

if(NV_REST_BUILD_EXAMPLE)
    add_subdirectory(examples/hello-world build-examples-hello-world)
endif()

message(STATUS "")
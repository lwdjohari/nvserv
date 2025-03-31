cmake_minimum_required(VERSION 3.10)
project(nvserv CXX)





message(STATUS "Nvserv Socket: ON")

include(ProjectCXX)
set(ISROOT FALSE)
NV_DETECT_IS_ROOT_PROJECT(ISROOT)
message(STATUS "NvServ Root Project: ${ISROOT} ${PCN_CXX_VERSION}")


# Add Unit Test Lib Catch2
if(NVSERV_USE_CATCH)
 message(STATUS  "CATCH2::ADD_LIB.")
 find_package(Catch2 3 REQUIRED)
endif()

find_package(Threads REQUIRED)




if (TARGET absl::base)
    message(STATUS "Nvrest lib ABSL: Abseil lib are already set, use ABSL from project.")
else ()
    message(STATUS "Nvrest lib ABSL: FATAL ERROR Abseil not found!")
endif ()



if(NOT nvcore_FOUND)
    message(STATUS "Nvserv::rest lib nvcore: Initialize NvCore lib.")
    add_subdirectory(deps/nvcore/ build-nvcore)
else()
    message(STATUS "Nvserv::rest lib nvcore: nvcore lib are already set, use nvcore from project.")
endif()

#asio

# Prevent multiple inclusion by checking if Asio is already added
set(ASIO_SOURCE_DIR "${CMAKE_SOURCE_DIR}/deps/asio")
add_definitions(-DASIO_STANDALONE)

#Main headers and sources
file(GLOB_RECURSE SOURCES_NVSERV_REST CONFIGURE_DEPENDS
    ${CMAKE_CURRENT_SOURCE_DIR}/src/*.h
    ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/src/*.s
)


# # nvserv::core
add_library(${PROJECT_NAME}_socket STATIC ${SOURCES_NVSERV_REST} )
target_link_libraries(${PROJECT_NAME}_socket  
    PUBLIC
        ${PROJECT_NAME}::core 
    PRIVATE
        
    )
set_target_properties(${PROJECT_NAME}_socket PROPERTIES LINKER_LANGUAGE CXX)
target_compile_features(${PROJECT_NAME}_socket PUBLIC ${CXX_FEATURE})
target_include_directories(${PROJECT_NAME}_socket
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/src/
    PRIVATE
        ${ASIO_SOURCE_DIR}/asio/include
)


add_library(${PROJECT_NAME}::socket ALIAS ${PROJECT_NAME}_socket )
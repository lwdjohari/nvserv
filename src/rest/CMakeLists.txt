cmake_minimum_required(VERSION 3.10)
project(nvserv CXX)



#  feature
# Network
option(NVSERV_FEATURE_ENVOY "Integrate Envoy Dataplane Library" OFF)

# Print the Piconout FEATURES
message(STATUS "Piconout FEATURES.")
message(STATUS "Core: ON")

message(STATUS "NvLog: ON")



message(STATUS "")

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


# if(NOT nvcore_FOUND)
#     message(STATUS "Nvql lib nvcore: Initialize NvCore lib.")
#     add_subdirectory(src/core/ build-nvserv_core)
# else()
#     message(STATUS "Nvql lib nvcore: Abseil lib are already set, use ABSL from project.")
# endif()


if (TARGET absl::base)
    message(STATUS "Nvrest lib ABSL: Abseil lib are already set, use ABSL from project.")
else ()
    message(STATUS "Nvrest lib ABSL: FATAL ERROR Abseil not found!")
endif ()


message(STATUS  "nghttp2 lib: ON")
option(ENABLE_LIB_ONLY ON)
set(ENABLE_LIB_ONLY ON)
set(BUILD_SHARED_LIBS OFF)
set(BUILD_STATIC_LIBS ON)
# set(WITH-BORINGSSL ON)

add_subdirectory(../../deps/nghttp2-override build-nghttp2)

if(NOT nvcore_FOUND)
    message(STATUS "Nvserv::rest lib nvcore: Initialize NvCore lib.")
    add_subdirectory(deps/nvcore/ build-nvcore)
else()
    message(STATUS "Nvserv::rest lib nvcore: nvcore lib are already set, use nvcore from project.")
endif()


#Main headers and sources
file(GLOB_RECURSE SOURCES_NVSERV_REST CONFIGURE_DEPENDS
    ${CMAKE_CURRENT_SOURCE_DIR}/src/*.h
    ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/src/*.s
)


# # nvserv::core
# add_library(${PROJECT_NAME}_rest STATIC ${SOURCES_NVSERV_REST} )
# target_link_libraries(${PROJECT_NAME}_rest  
#     PUBLIC
#         ${PROJECT_NAME}::core 
#     PRIVATE
#         ${H2O_LIBRARIES}
#     )
# set_target_properties(${PROJECT_NAME}_rest PROPERTIES LINKER_LANGUAGE CXX)
# target_compile_features(${PROJECT_NAME}_rest PUBLIC ${CXX_FEATURE})
# target_include_directories(${PROJECT_NAME}_rest
#     PUBLIC
#     ${CMAKE_CURRENT_SOURCE_DIR}/src/
#     PRIVATE
#         ${H2O_INCLUDE_DIRS}
# )



# add_library(${PROJECT_NAME}::rest ALIAS ${PROJECT_NAME}_rest )
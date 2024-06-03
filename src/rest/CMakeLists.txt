cmake_minimum_required(VERSION 3.10)
project(nvserv CXX)


# Include custom FindH2O module
find_package(Wslay REQUIRED)
if(NOT WSLAY_FOUND)
    message(FATAL_ERROR "wslay library not found")
endif()
find_package(H2O REQUIRED)


#Main headers and sources
file(GLOB_RECURSE SOURCES_NVSERV_REST CONFIGURE_DEPENDS
    ${CMAKE_CURRENT_SOURCE_DIR}/src/*.h
    ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/src/*.s
)


# nvserv::core
add_library(${PROJECT_NAME}_rest STATIC ${SOURCES_NVSERV_REST} )
target_link_libraries(${PROJECT_NAME}_rest  
    PUBLIC
        ${PROJECT_NAME}::core 
    PRIVATE
        ${H2O_LIBRARIES}
    )
set_target_properties(${PROJECT_NAME}_rest PROPERTIES LINKER_LANGUAGE CXX)
target_compile_features(${PROJECT_NAME}_rest PUBLIC ${CXX_FEATURE})
target_include_directories(${PROJECT_NAME}_rest
    PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/src/
    PRIVATE
        ${H2O_INCLUDE_DIRS}
)



add_library(${PROJECT_NAME}::rest ALIAS ${PROJECT_NAME}_rest )
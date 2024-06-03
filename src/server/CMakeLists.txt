cmake_minimum_required(VERSION 3.10)
project(nvserv CXX)



#Main headers and sources
file(GLOB_RECURSE SOURCES_NVSERV_SERVER CONFIGURE_DEPENDS
    ${CMAKE_CURRENT_SOURCE_DIR}/src/*.h
    ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/src/*.s
)


# nvserv::server
add_library(${PROJECT_NAME}_server STATIC ${SOURCES_NVSERV_SERVER} )
target_link_libraries(${PROJECT_NAME}_server  
    PUBLIC
        ${PROJECT_NAME}::core 
    )
set_target_properties(${PROJECT_NAME}_server PROPERTIES LINKER_LANGUAGE CXX)
target_compile_features(${PROJECT_NAME}_server PUBLIC ${CXX_FEATURE})
target_include_directories(${PROJECT_NAME}_server
    PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/src/
)

add_library(${PROJECT_NAME}::server ALIAS ${PROJECT_NAME}_server )
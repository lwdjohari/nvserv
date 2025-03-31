# The MIT License (MIT)
#
# Copyright (c) 2024 Linggawasistha Djohari
#
# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documentation files (the "Software"), to deal
# in the Software without restriction, including without limitation the rights
# to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of the Software, and to permit persons to whom the Software is
# furnished to do so, subject to the following conditions:
#
# The above copyright notice and this permission notice shall be included in all
# copies or substantial portions of the Software.
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
# SOFTWARE.
#

# nvserv_generate_protos Usage Example
# ------------------------------------------------------
# # Define proto files, source, and output directories
# set(PROTO_FILES ${CMAKE_CURRENT_SOURCE_DIR}/example1.proto ${CMAKE_CURRENT_SOURCE_DIR}/example2.proto)
# set(GENERATED_SRC_DIR ${CMAKE_CURRENT_BINARY_DIR}/generated)
# set(PROTO_SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR})

# # Variables to hold generated sources and headers
# set(PROTO_GENERATED_SOURCE "")
# set(PROTO_GENERATED_HEADER "")
#
# # Call the function to generate protobuf and gRPC files
# nvserv_generate_protos(
#       ${PROTO_FILES} 
#       ${GENERATED_SRC_DIR} 
#       ${PROTO_SRC_DIR} 
#       PROTO_GENERATED_SOURCE 
#       PROTO_GENERATED_HEADER 
#   generate_protos_target)
#
# # Use the generated sources in a library
# add_library(the_proto_lib ${PROTO_GENERATED_SOURCE} ${PROTO_GENERATED_HEADER})
# target_include_directories(the_proto_lib PRIVATE ${GENERATED_SRC_DIR})
# target_link_libraries(the_proto_lib PRIVATE gRPC::grpc++ protobuf::libprotobuf)

function(nvserv_generate_protos 
    PROTO_FILES 
    GENERATED_SRC_DIR 
    PROTO_SRC_DIR 
    GENERATED_SRCS_VAR 
    GENERATED_HDRS_VAR 
    TARGET_NAME)

    # Ensure required executables are available
    if(NOT Protobuf_PROTOC_EXECUTABLE OR NOT EXISTS ${Protobuf_PROTOC_EXECUTABLE})
        message(FATAL_ERROR "Protobuf compiler not found or not set. Please ensure gRPC and Protobuf are built correctly.")
    endif()

    if(NOT gRPC_CPP_PLUGIN_EXECUTABLE OR NOT EXISTS ${gRPC_CPP_PLUGIN_EXECUTABLE})
        message(FATAL_ERROR "gRPC C++ plugin not found or not set. Please ensure gRPC is built correctly.")
    endif()

    # Create the output directory for generated files
    file(MAKE_DIRECTORY ${GENERATED_SRC_DIR})

    # Temporary lists to collect generated files
    set(LOCAL_GENERATED_SRCS "")
    set(LOCAL_GENERATED_HDRS "")

    # Generate C++ source and header files for each proto during the configure step
    foreach(PROTO_FILE ${PROTO_FILES})
        get_filename_component(PROTO_FILE_NAME ${PROTO_FILE} NAME_WE)
        message(STATUS "Compiling proto: ${PROTO_FILE_NAME}")

        # Define output files
        set(PB_CC_FILE ${GENERATED_SRC_DIR}/${PROTO_FILE_NAME}.pb.cc)
        set(PB_H_FILE ${GENERATED_SRC_DIR}/${PROTO_FILE_NAME}.pb.h)
        set(GRPC_CC_FILE ${GENERATED_SRC_DIR}/${PROTO_FILE_NAME}.grpc.pb.cc)
        set(GRPC_H_FILE ${GENERATED_SRC_DIR}/${PROTO_FILE_NAME}.grpc.pb.h)

        # Protobuf generation
        execute_process(
            COMMAND ${Protobuf_PROTOC_EXECUTABLE}
                    --cpp_out=${GENERATED_SRC_DIR}
                    -I ${PROTO_SRC_DIR}
                    ${PROTO_FILE}
            WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
            RESULT_VARIABLE PROTOBUF_RESULT
            ERROR_VARIABLE PROTOBUF_ERROR
        )
        if(NOT PROTOBUF_RESULT EQUAL 0)
            message(FATAL_ERROR "Protobuf compilation failed: ${PROTOBUF_ERROR}")
        endif()

        # gRPC generation
        execute_process(
            COMMAND ${Protobuf_PROTOC_EXECUTABLE}
                    --grpc_out=${GENERATED_SRC_DIR}
                    --plugin=protoc-gen-grpc=${gRPC_CPP_PLUGIN_EXECUTABLE}
                    -I ${PROTO_SRC_DIR}
                    ${PROTO_FILE}
            WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
            RESULT_VARIABLE GRPC_RESULT
            ERROR_VARIABLE GRPC_ERROR
        )
        if(NOT GRPC_RESULT EQUAL 0)
            message(FATAL_ERROR "gRPC compilation failed: ${GRPC_ERROR}")
        endif()

        # Add generated files to the local lists
        list(APPEND LOCAL_GENERATED_SRCS ${PB_CC_FILE} ${GRPC_CC_FILE})
        list(APPEND LOCAL_GENERATED_HDRS ${PB_H_FILE} ${GRPC_H_FILE})
    endforeach()

    # Ensure that generated files are produced before the main target
    add_custom_target(${TARGET_NAME} ALL DEPENDS ${LOCAL_GENERATED_SRCS} ${LOCAL_GENERATED_HDRS})

    # Export local lists to the caller
    set(${GENERATED_SRCS_VAR} ${LOCAL_GENERATED_SRCS} PARENT_SCOPE)
    set(${GENERATED_HDRS_VAR} ${LOCAL_GENERATED_HDRS} PARENT_SCOPE)
endfunction()
cmake_minimum_required(VERSION 2.6)
project(thriftygramophone)

enable_testing()


set(THRIFT_HEADER thrift/Thrift.h)
find_path(THRIFT_INCLUDE_DIR ${THRIFT_HEADER})
if (NOT THRIFT_INCLUDE_DIR)
  message(SEND_ERROR "${THRIFT_HEADER} not found")
endif()

set(THRIFT_LIB_NAME thrift)
find_library(THRIFT_LIBRARY ${THRIFT_LIB_NAME} DOC "foobas")
if (NOT THRIFT_LIBRARY)
  message(SEND_ERROR "${THRIFT_LIB_NAME} not found")
endif()

include_directories(${THRIFT_INCLUDE_DIR})

add_subdirectory(src)
add_subdirectory(test)

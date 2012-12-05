find_package(GTest 1.6.0)

if (GTEST_FOUND)
  set(PROJECT_TEST_NAME "thriftgramophone_test")
  include_directories(${GTEST_INCLUDE_DIRS})

  add_executable(${PROJECT_TEST_NAME} "devices_test.cpp")
  target_link_libraries(${PROJECT_TEST_NAME} tgramophone ${GTEST_BOTH_LIBRARIES} pthread ${THRIFT_LIBRARY})

  add_test(${PROJECT_TEST_NAME} ${PROJECT_TEST_NAME})
endif()
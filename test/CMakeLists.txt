find_package(GTest 1.6.0)

if (GTEST_FOUND)
  find_package(Boost REQUIRED COMPONENTS thread)

  set(PROJECT_TEST_NAME "thriftygramophone_test")
  include_directories(${GTEST_INCLUDE_DIRS} ${Boost_INCLUDE_DIRS})

  add_executable(${PROJECT_TEST_NAME} "devices_test.cpp" "service_test.cpp")
  target_link_libraries(${PROJECT_TEST_NAME} tgramophone ${GTEST_BOTH_LIBRARIES} pthread ${THRIFT_LIBRARY} ${Boost_LIBRARIES})

  add_test(${PROJECT_TEST_NAME} ${PROJECT_TEST_NAME})
endif()
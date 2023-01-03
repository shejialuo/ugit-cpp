enable_testing()

add_executable(
  utilTest
  utilTest.cpp
)

add_executable(
  diffTest
  diffTest.cpp
)

target_include_directories(utilTest PRIVATE ../)
target_include_directories(diffTest PRIVATE ../)

target_link_libraries(
  utilTest
  data
  GTest::gtest_main
)

target_link_libraries(
  diffTest
  data
  GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(utilTest)
gtest_discover_tests(diffTest)

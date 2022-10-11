enable_testing()

add_executable(
  utilTest
  utilTest.cpp
)

target_include_directories(utilTest PRIVATE ../)

target_link_libraries(
  utilTest
  data
  GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(utilTest)

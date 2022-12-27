# Configure the test suite with GoogleTest
add_executable(run_tests test_all.cpp)
target_link_libraries(
  run_tests
  GTest::gtest_main
)

# Execute the tests
include(GoogleTest)
gtest_discover_tests(run_tests)
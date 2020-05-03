# Locate GTest
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})
 
# Link run_tests with what we want to test and the GTest and pthread library
add_executable(run_tests test_all.cpp)
target_link_libraries(run_tests ${GTEST_LIBRARIES} pthread)
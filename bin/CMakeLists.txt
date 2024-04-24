
project(BINARIES)


add_executable(TEST_INTEGERS ${PROJECT_SOURCE_DIR}/test/integers.cpp)
target_link_libraries(TEST_INTEGERS INTEGERS)

add_executable(TEST_PRIME_TESTS ${PROJECT_SOURCE_DIR}/test/prime_tests.cpp)
target_link_libraries(TEST_PRIME_TESTS INTEGERS PRIME_TESTS)
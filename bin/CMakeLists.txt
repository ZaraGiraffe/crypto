
project(BINARIES)


add_executable(TEST_INTEGERS ${PROJECT_SOURCE_DIR}/test/integers.cpp)
target_link_libraries(TEST_INTEGERS INTEGERS)

add_executable(TEST_PRIME_TESTS ${PROJECT_SOURCE_DIR}/test/prime_tests.cpp)
target_link_libraries(TEST_PRIME_TESTS INTEGERS PRIME_TESTS)

add_executable(TEST_PRIME_GEN ${PROJECT_SOURCE_DIR}/test/prime_gen.cpp)
target_link_libraries(TEST_PRIME_GEN INTEGERS PRIME_TESTS PRIME_GEN)

add_executable(TEST_RSA ${PROJECT_SOURCE_DIR}/test/rsa.cpp)
target_link_libraries(TEST_RSA INTEGERS RSA PRIME_GEN)


project(SRC)

add_library(INTEGERS INTERFACE)
target_include_directories(INTEGERS INTERFACE ${PROJECT_SOURCE_DIR}/integers)

add_library(PRIME_TESTS INTERFACE)
target_include_directories(PRIME_TESTS INTERFACE ${PROJECT_SOURCE_DIR}/prime_tests)
target_link_libraries(PRIME_TESTS INTERFACE INTEGERS)

add_library(PRIME_GEN INTERFACE)
target_include_directories(PRIME_GEN INTERFACE ${PROJECT_SOURCE_DIR}/prime_gen)
target_link_libraries(PRIME_GEN INTERFACE INTEGERS INTERFACE PRIME_TESTS)

add_library(RSA INTERFACE)
target_include_directories(RSA INTERFACE ${PROJECT_SOURCE_DIR}/rsa)
target_link_libraries(RSA INTERFACE INTEGERS)


project(SRC)

add_library(INTEGERS INTERFACE)
target_include_directories(INTEGERS INTERFACE ${PROJECT_SOURCE_DIR}/integers)

add_library(PRIME_TESTS INTERFACE)
target_include_directories(PRIME_TESTS INTERFACE ${PROJECT_SOURCE_DIR}/prime_tests)
target_link_libraries(PRIME_TESTS INTERFACE INTEGERS)

add_library(PRIME_GEN INTERFACE)
target_include_directories(PRIME_TESTS INTERFACE ${PROJECT_SOURCE_DIR}/prime_gen)
target_link_libraries(PRIME_TESTS INTERFACE INTEGERS INTERFACE PRIME_TESTS)

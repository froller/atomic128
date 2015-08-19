cmake_minimum_required(VERSION 3.0)

set(CMAKE_C_COMPILER "clang")

if(POLICY CMP0056)
    cmake_policy(SET CMP0056 NEW)
endif(POLICY CMP0056)

project(atomic128)

# Library

set(LIB_SOURCES "atomic128.c")
set_source_files_properties(
    "atomic128.c"
    PROPERTIES
    COMPILE_FLAGS "-fasm-blocks"
    LANGUAGE "C"
)

add_library(atomic128_static STATIC ${LIB_SOURCES})

set_target_properties(
    atomic128_static
    PROPERTIES
    OUTPUT_NAME atomic128
)

add_custom_command(
    TARGET atomic128_static
    POST_BUILD
    COMMAND "${CMAKE_CURRENT_SOURCE_DIR}/hackobj.sh"
    COMMENT "Hacking function names"
)

# Test samples

enable_testing()

file(GLOB TEST_SOURCES "test_*.c")
set_source_files_properties(
    ${TEST_SOURCES}
    PROPERTIES
    COMPILE_FLAGS "-Wno-constant-logical-operand -Wno-format"
    LANGUAGE "C"
)

add_executable(test_sltas "test_sltas.c")
target_link_libraries(test_sltas "${CMAKE_CURRENT_BINARY_DIR}/libatomic128.a")

add_executable(test_svcas "test_svcas.c")
target_link_libraries(test_svcas "${CMAKE_CURRENT_BINARY_DIR}/libatomic128.a")


# Test definitions

add_test(
    NAME __sync_lock_test_and_set_16
    COMMAND "${CMAKE_CURRENT_BINARY_DIR}/test_sltas"
)
add_test(
    NAME __sync_val_compare_and_swap_16
    COMMAND "${CMAKE_CURRENT_BINARY_DIR}/test_svcas"
)

# Install

include(GNUInstallDirs)
install(
    TARGETS atomic128_static
    ARCHIVE DESTINATION "${CMAKE_INSTALL_LIBDIR}"
)


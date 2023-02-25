cmake_minimum_required(VERSION "3.22")

project("c-utils")

#
# Common settings
# Generate `compile_commands.json` for `Neovim` LSP needed
#
set(CMAKE_EXPORT_COMPILE_COMMANDS 1)
set(CMAKE_BUILD_TYPE "Debug")
set(CMAKE_C_FLAGS "-pedantic-errors -std=gnu17")
set(CMAKE_CXX_FLAGS "-pedantic-errors -Wc99-extensions -Wvla-extension -Wc11-extensions -Wc11-extensions -std=gnu++11")

enable_testing()
find_package(GTest REQUIRED)

add_executable("${PROJECT_NAME}-unit-test"
    "../../src/utils/log.c"
    "../../src/utils/collections/single_link_list.c"
    "../../src/utils/collections/vector.c"
    "../../src/utils/memory.c"
    "../../src/utils/string.c"
    "../../src/utils/hex_buffer.c"
    "../../src/utils/file.c"
    "../../src/test/unit/utils/file_test.cpp"
    "../../src/test/unit/utils/hex_buffer_test.cpp"
    "../../src/test/unit/utils/data_types_test.cpp"
    "../../src/test/unit/utils/collections/single_link_list_test.cpp"
    "../../src/test/unit/utils/collections/vector_test.cpp"
    "../../src/test/unit/utils/string_test.cpp"
    "../../src/main.cpp")

target_link_libraries("${PROJECT_NAME}-unit-test" GTest::gtest GTest::gtest_main)

# target_compile_definitions("${PROJECT_NAME}-unit-test" PRIVATE ENABLE_DEBUG_LOG)

# -----------------------------------------------------------------------------
# Add a test to the project to be run by `ctest(1).`
#
# More details from here:
# https://cmake.org/cmake/help/latest/command/add_test.html?highlight=add_test
# -----------------------------------------------------------------------------
# add_test(RunAllTest "${PROJECT_NAME}")
# add_test(RunsingleLinkTest single_link_list_test)

message(">>> CMAKE_EXPORT_COMPILE_COMMANDS: ${CMAKE_EXPORT_COMPILE_COMMANDS}")
message(">>> CMAKE_SYSTEM_NAME: ${CMAKE_SYSTEM_NAME}")
message(">>> CMAKE_BUILD_TYPE: ${CMAKE_BUILD_TYPE}")
message(">>> CMAKE_C_COMPILER: ${CMAKE_C_COMPILER}")
message(">>> CMAKE_C_FLAGS: ${CMAKE_C_FLAGS}")
message(">>> CMAKE_C_FLAGS_DEBUG: ${CMAKE_C_FLAGS_DEBUG}")
message(">>> CMAKE_C_FLAGS_RELEASE: ${CMAKE_C_FLAGS_RELEASE}")
message(">>> CMAKE_CXX_COMPILER: ${CMAKE_CXX_COMPILER}")
message(">>> CMAKE_CXX_FLAGS: ${CMAKE_CXX_FLAGS}")
message(">>> CMAKE_CXX_FLAGS_DEBUG: ${CMAKE_CXX_FLAGS_DEBUG}")
message(">>> CMAKE_CXX_FLAGS_RELEASE: ${CMAKE_CXX_FLAGS_RELEASE}")
message(">>> GTest_FOUND: ${GTest_FOUND}")

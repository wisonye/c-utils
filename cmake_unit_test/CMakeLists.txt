cmake_minimum_required(VERSION "3.22")

project("c-utils")

enable_testing()
find_package(GTest REQUIRED)

add_executable("${PROJECT_NAME}-unit-test"
    "../src/utils/log.c"
    "../src/utils/collections/single_link_list.c"
    "../src/utils/collections/single_link_list_test.cpp"
    "../src/utils/collections/vector.c"
    "../src/utils/collections/vector_test.cpp"
    "../src/utils/memory.c"
    "../src/utils/string.c"
    "../src/utils/string_test.cpp"
    "../src/utils/hex_buffer.c"
    "../src/utils/hex_buffer_test.cpp"
    "../src/utils/data_types_test.cpp"
    "../src/utils/file.c"
    "../src/utils/file_test.cpp"
    "../src/main.cpp")

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

cmake_minimum_required(VERSION "3.22")

project("c-utils")

add_executable("${PROJECT_NAME}"
    "../src/utils/log.c"
    "../src/utils/collections/single_link_list.c"
    "../src/utils/string.c"
    "../src/utils/hex_buffer.c"
    "../src/utils/vector.c"
    "../src/utils/memory.c"
    "../src/utils/timer.c"
    "../src/main.c")

target_compile_definitions("${PROJECT_NAME}" PRIVATE ENABLE_DEBUG_LOG)

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

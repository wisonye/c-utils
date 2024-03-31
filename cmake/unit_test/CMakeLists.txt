cmake_minimum_required(VERSION "3.22")

project("c-utils")

#
# Common settings
# Generate `compile_commands.json` for `Neovim` LSP needed
#
set(CMAKE_EXPORT_COMPILE_COMMANDS 1)
set(CMAKE_BUILD_TYPE "Debug")
set(CMAKE_C_FLAGS "-pedantic -ansi -Wall -Werror -Wextra -std=gnu17")

#
# Extra include path for `unity` test framework
#
option(USE_CUSTOM_UNITY_INSTALL_PATH "Enable custom 'unity' install path" OFF)

if (USE_CUSTOM_UNITY_INSTALL_PATH)
	set(MY_UNITY_INSTALL_INCLUDE_PATH ${MY_UNITY_INSTALL_INCLUDE_PATH})
	set(MY_UNITY_INSTALL_LIB_PATH ${MY_UNITY_INSTALL_LIB_PATH})

	include_directories("${MY_UNITY_INSTALL_INCLUDE_PATH}")
	link_directories("${MY_UNITY_INSTALL_LIB_PATH}")

	message(">>>")
    message(">>> [ Use custom Unity install path ].")
    message(">>> \tMY_UNITY_INSTALL_INCLUDE_PATH: ${MY_UNITY_INSTALL_INCLUDE_PATH}")
    message(">>> \tMY_UNITY_INSTALL_LIB_PATH: ${MY_UNITY_INSTALL_LIB_PATH}")
	message(">>>\n")
endif()

add_executable("${PROJECT_NAME}-unit-test"
    "../../src/utils/log.c"
    "../../src/utils/memory.c"
    "../../src/utils/heap_string.c"
    "../../src/utils/hex_buffer.c"
    "../../src/utils/file.c"
    "../../src/test/utils/hex_buffer_test.c"
    "../../src/test/utils/data_types_test.c"
    "../../src/test/utils/file_test.c"
    "../../src/test/utils/string_test.c"
    "../../src/unit_test.c")

target_link_libraries("${PROJECT_NAME}-unit-test" unity)

# target_compile_definitions("${PROJECT_NAME}-unit-test" PRIVATE ENABLE_DEBUG_LOG)


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

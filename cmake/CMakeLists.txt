cmake_minimum_required(VERSION "3.22")

project("c-utils")

#
# Common settings
# Generate `compile_commands.json` for `Neovim` LSP needed
#
set(CMAKE_EXPORT_COMPILE_COMMANDS 1)
set(CMAKE_BUILD_TYPE "Debug")
set(CMAKE_C_FLAGS "-pedantic-errors -std=gnu17")

#
# Use different `C` compilation flags based on different optional settings
#
option(USE_VALGRIND "Enable 'valgrind' for memory leaking detection" OFF)
option(USE_ADDRESS_SANITIZER "Enable 'address_sanitizer' for memory leaking detection" OFF)
option(USE_ADDRESS_SANITIZER_FOR_FREE_BSD "Enable 'address_sanitizer' (FreeBSD) for memory leaking detection" OFF)

if (USE_VALGRIND)
    set(CMAKE_BUILD_TYPE "Release")
    message(">>>\n>>> Use 'Valgrind' for memory leaking detection and switch to Release build\n>>>")
# elseif ((USE_ADDRESS_SANITIZER) OR (USE_ADDRESS_SANITIZER_FOR_FREE_BSD))
elseif (USE_ADDRESS_SANITIZER )
    set(CMAKE_C_FLAGS "-pedantic-errors -std=gnu17 -fsanitize=address -O1 -fno-omit-frame-pointer")
    message(">>>\n>>> Use 'Address Sanitizer' for memory leaking detection\n>>>")
elseif (USE_ADDRESS_SANITIZER_FOR_FREE_BSD)
    set(CMAKE_C_FLAGS "-pedantic-errors -std=gnu17 -fsanitize=address -O1 -fno-omit-frame-pointer")
    message(">>>\n>>> Use 'Address Sanitizer' (FreeBSD) for memory leacking detection\n>>>")
endif()

add_executable("${PROJECT_NAME}"
    "../src/utils/log.c"
    "../src/utils/collections/single_link_list.c"
    "../src/utils/collections/vector.c"
    "../src/utils/string.c"
    "../src/utils/hex_buffer.c"
    "../src/utils/memory.c"
    "../src/utils/timer.c"
    "../src/utils/file.c"
    "../src/utils/random.c"
    "../src/main.c")

# target_compile_definitions("${PROJECT_NAME}" PRIVATE ENABLE_DEBUG_LOG ENABLE_PRINT_STRING_MEMORY)
target_compile_definitions("${PROJECT_NAME}" PRIVATE ENABLE_DEBUG_LOG)

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

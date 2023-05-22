cmake_minimum_required(VERSION "3.22")

project("c-utils-demo")

#
# Common settings
# Generate `compile_commands.json` for `Neovim` LSP needed
#
set(CMAKE_EXPORT_COMPILE_COMMANDS 1)
set(CMAKE_BUILD_TYPE "Debug")
set(CMAKE_C_FLAGS "-pedantic-errors -Wall -Werror -Wextra -std=gnu17")


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
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fsanitize=address -O1 -fno-omit-frame-pointer")
    message(">>>\n>>> Use 'Address Sanitizer' for memory leaking detection\n>>>")
elseif (USE_ADDRESS_SANITIZER_FOR_FREE_BSD)
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fsanitize=address -O1 -fno-omit-frame-pointer")
    message(">>>\n>>> Use 'Address Sanitizer' (FreeBSD) for memory leacking detection\n>>>")
endif()

add_executable("${PROJECT_NAME}"
    "../src/utils/log.c"
    "../src/utils/collections/single_link_list.c"
    "../src/utils/collections/vector.c"
    "../src/utils/str.c"
    "../src/utils/hex_buffer.c"
    "../src/utils/memory.c"
    "../src/utils/timer.c"
    "../src/utils/file.c"
    "../src/utils/random.c"
    "../src/main.c")

# target_compile_definitions("${PROJECT_NAME}" PRIVATE ENABLE_DEBUG_LOG ENABLE_PRINT_STRING_MEMORY)
target_compile_definitions("${PROJECT_NAME}" PRIVATE ENABLE_DEBUG_LOG)

# -----------------------------------------------------------------------------
# Compile the particular source code as a static/dynamic library
#
# - static lib:  lib${LIBRARY_NAME}.a
# - dynamic lib: lib${LIBRARY_NAME}.so
#
# `add_library`: Adds a library target called <name> to be built from the source
#                files listed in the command invocation
#
# syntax: add_library(<name> [STATIC | SHARED | MODULE]
#           [EXCLUDE_FROM_ALL]
#           source1 [source2 ...])
#
# More details from here:
# https://cmake.org/cmake/help/v3.0/command/add_library.html?highlight=add_library
# -----------------------------------------------------------------------------

set(UTILS_LIBRARY_NAME "c-utils")
set(UTILS_LIBRARY_SOURCE_FILE
    "../src/utils/file.c"
    "../src/utils/hex_buffer.c"
    "../src/utils/log.c"
    "../src/utils/memory.c"
    "../src/utils/random.c"
    "../src/utils/str.c"
    "../src/utils/timer.c"
)
set(UTILS_LIBRARY_HEADER_FILE
    "../src/utils/bits.h"
    "../src/utils/data_types.h"
    "../src/utils/file.h"
    "../src/utils/hex_buffer.h"
    "../src/utils/log.h"
    "../src/utils/memory.h"
    "../src/utils/random.h"
    "../src/utils/smart_ptr.h"
    "../src/utils/str.h"
    "../src/utils/timer.h"
)
add_library("${UTILS_LIBRARY_NAME}" SHARED ${UTILS_LIBRARY_SOURCE_FILE})
# add_library("${UTILS_LIBRARY_NAME}" STATIC "${UTILS_LIBRARY_SOURCE_FILE}")

# -----------------------------------------------------------------------------
# The settings below just copy the target into different output folder
#
# By default, `make install` copies all targets to `/usr/local` which means:
#
# /usr/local/bin
# /usr/local/lib
# /usr/local/include
#
# Of course, you can change it by running `cmake` like below if you want:
#
# `cmake .. -DCMAKE_INSTALL_PREFIX=/cpp/build`
#
#  After that, `make install` copies all targets to:
#
# /cpp/build/bin
# /cpp/build/lib
# /cpp/build/include
#
#
# syntax: install(TARGETS targets... [EXPORT <export-name>]
#       [[ARCHIVE|LIBRARY|RUNTIME|FRAMEWORK|BUNDLE|
#         PRIVATE_HEADER|PUBLIC_HEADER|RESOURCE]
#        [DESTINATION <dir>]
#        [INCLUDES DESTINATION [<dir> ...]]
#        [PERMISSIONS permissions...]
#        [CONFIGURATIONS [Debug|Release|...]]
#        [COMPONENT <component>]
#        [OPTIONAL] [NAMELINK_ONLY|NAMELINK_SKIP]
#       ] [...]) 
#
#       `Executables` are treated as `RUNTIME` targets
#
# More details from here:
# https://cmake.org/cmake/help/v3.0/command/install.html?highlight=install
# -----------------------------------------------------------------------------
install(
    TARGETS "${UTILS_LIBRARY_NAME}"
    RUNTIME DESTINATION bin
    LIBRARY DESTINATION lib
)

# install(FILES "${UTILS_LIBRARY_HEADER_FILE}" DESTINATION include)
install(FILES "../src/utils/bits.h" DESTINATION "include/${UTILS_LIBRARY_NAME}")
install(FILES "../src/utils/data_types.h" DESTINATION "include/${UTILS_LIBRARY_NAME}")
install(FILES "../src/utils/file.h" DESTINATION "include/${UTILS_LIBRARY_NAME}")
install(FILES "../src/utils/hex_buffer.h" DESTINATION "include/${UTILS_LIBRARY_NAME}")
install(FILES "../src/utils/log.h" DESTINATION "include/${UTILS_LIBRARY_NAME}")
install(FILES "../src/utils/memory.h" DESTINATION "include/${UTILS_LIBRARY_NAME}")
install(FILES "../src/utils/random.h" DESTINATION "include/${UTILS_LIBRARY_NAME}")
install(FILES "../src/utils/smart_ptr.h" DESTINATION "include/${UTILS_LIBRARY_NAME}")
install(FILES "../src/utils/str.h" DESTINATION "include/${UTILS_LIBRARY_NAME}")
install(FILES "../src/utils/timer.h" DESTINATION "include/${UTILS_LIBRARY_NAME}")

#
# Debug messages
#
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
message(">>> UTILS_LIBRARY_NAME: ${UTILS_LIBRARY_NAME}")
message(">>> UTILS_LIBRARY_SOURCE_FILE: ${UTILS_LIBRARY_SOURCE_FILE}")
message(">>> UTILS_LIBRARY_HEADER_FILE: ${UTILS_LIBRARY_HEADER_FILE}")


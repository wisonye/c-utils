cmake_minimum_required(VERSION "3.22")

# Indicate the compliation environment (Host OS and CPU Arch): uname -s
# set(CMAKE_SYSTEM_NAME Darwin)
# set(CMAKE_SYSTEM_NAME FreeBSD)
# set(CMAKE_SYSTEM_PROCESSOR x86_64)

# -----------------------------------------------------------------------------
# Define project name. After this, we can use "${PROJECT_NAME}" var to 
# dereference/re-use the project name as a String value.
#
# More details from here:
# https://cmake.org/cmake/help/v3.0/command/project.html?highlight=project
# -----------------------------------------------------------------------------
project("c-utils")


# -----------------------------------------------------------------------------
# Enable verbose makefile
# -----------------------------------------------------------------------------
# set(CMAKE_VERBOSE_MAKEFILE TRUE)


# -----------------------------------------------------------------------------
# Compile and build executable
#
# `add_executable`: Adds an executable target called <name> to be built from the
#                   source files listed in the command invocation.
#
# syntax: add_executable(<name> [WIN32] [MACOSX_BUNDLE]
#              [EXCLUDE_FROM_ALL]
#              source1 [source2 ...])
#
# More details from here:
# https://cmake.org/cmake/help/v3.0/command/add_executable.html?highlight=add_executable
# -----------------------------------------------------------------------------
add_executable("${PROJECT_NAME}"
    "../src/utils/log.c"
    "../src/utils/collections/single_link_list.c"
    "../src/utils/string.c"
    "../src/utils/hex_buffer.c"
    "../src/utils/vector.c"
    "../src/main.c")



# -----------------------------------------------------------------------------
# Conditional compilation, it's equal to add a `#define MACRO_NAME` in your
# project source file.
#
# `target_compile_definitions`: Specify compile definitions to use when
#                               compiling a given <target. The named <target>
#                               must have been created by a command such as
#                               `add_executable()` or `add_library()` and must
#                               not be an Imported Target.
#
# syntax: target_compile_definitions(<target>
#           <INTERFACE|PUBLIC|PRIVATE> [items1...]
#           [<INTERFACE|PUBLIC|PRIVATE> [items2...] ...])
#
# `PUBLIC` or `INTERFACE` publishes the compile definitions required to compile
# against the `headers` for the target.
#
# More details from here:
# https://cmake.org/cmake/help/v3.0/command/target_compile_definitions.html?highlight=target_compile_de
# -----------------------------------------------------------------------------
target_compile_definitions("${PROJECT_NAME}" PRIVATE ENABLE_DEBUG_LOG)


# -----------------------------------------------------------------------------
# Print out cmake vars for debugging `MakeLists.txt` purpose
# -----------------------------------------------------------------------------
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



# `c-utils`

This is my personal `C` utilities which contains the following modules:

- `Collection`: All kinds of list, stack and queue.

- `String`: Wrap and hide all `null-terminated` C-style string in `struct`,
hide the `null-terminated` detail and pointer, just deal with normal function
call.

- `Vector`: Growable vector

</br>

All source code located in `src/utils`, the `src/main.cpp` is just a unit test.
You need to install `GoogleTest` if want to run it.

</br>

Why `main.cpp` in a `C` project?

That's because `GoogleTest` only work for `CPP`, but it doesn't affect all your
C source code:)

</br>

### 1. Make sure you compile and install `GoogleTest`

```bash
cd ~/temp
git clone https://github.com/google/googletest.git -b release-1.12.1
cd googletest        # Main directory of the cloned repository.
mkdir build          # Create a directory to hold the build output.
cd build
cmake .. -DBUILD_GMOCK=OFF

# -- The C compiler identification is Clang 14.0.5
# -- The CXX compiler identification is Clang 14.0.5
# -- Detecting C compiler ABI info
# -- Detecting C compiler ABI info - done
# -- Check for working C compiler: /usr/bin/cc - skipped
# -- Detecting C compile features
# -- Detecting C compile features - done
# -- Detecting CXX compiler ABI info
# -- Detecting CXX compiler ABI info - done
# -- Check for working CXX compiler: /usr/bin/c++ - skipped
# -- Detecting CXX compile features
# -- Detecting CXX compile features - done
# -- Found Python: /usr/local/bin/python3.9 (found version "3.9.16") found components: Interpreter
# -- Performing Test CMAKE_HAVE_LIBC_PTHREAD
# -- Performing Test CMAKE_HAVE_LIBC_PTHREAD - Failed
# -- Looking for pthread_create in pthreads
# -- Looking for pthread_create in pthreads - not found
# -- Looking for pthread_create in pthread
# -- Looking for pthread_create in pthread - found
# -- Found Threads: TRUE
# -- Configuring done
# -- Generating done
# -- Build files have been written to: /usr/home/wison/googletest/build
```

</br>

Install headers and libs:

```bash
doas make install

# [ 25%] Building CXX object googletest/CMakeFiles/gtest.dir/src/gtest-all.cc.o
# [ 50%] Linking CXX static library ../lib/libgtest.a
# [ 50%] Built target gtest
# [ 75%] Building CXX object googletest/CMakeFiles/gtest_main.dir/src/gtest_main.cc.o
# [100%] Linking CXX static library ../lib/libgtest_main.a
# [100%] Built target gtest_main
# Install the project...
# -- Install configuration: ""
# -- Installing: /usr/local/lib/cmake/GTest/GTestTargets.cmake
# -- Installing: /usr/local/lib/cmake/GTest/GTestTargets-noconfig.cmake
# -- Installing: /usr/local/lib/cmake/GTest/GTestConfigVersion.cmake
# -- Installing: /usr/local/lib/cmake/GTest/GTestConfig.cmake
# -- Up-to-date: /usr/local/include
# -- Installing: /usr/local/include/gtest
# -- Installing: /usr/local/include/gtest/internal
# -- Installing: /usr/local/include/gtest/internal/gtest-death-test-internal.h
# -- Installing: /usr/local/include/gtest/internal/gtest-port.h
# -- Installing: /usr/local/include/gtest/internal/gtest-type-util.h
# -- Installing: /usr/local/include/gtest/internal/gtest-string.h
# -- Installing: /usr/local/include/gtest/internal/custom
# -- Installing: /usr/local/include/gtest/internal/custom/gtest-port.h
# -- Installing: /usr/local/include/gtest/internal/custom/README.md
# -- Installing: /usr/local/include/gtest/internal/custom/gtest-printers.h
# -- Installing: /usr/local/include/gtest/internal/custom/gtest.h
# -- Installing: /usr/local/include/gtest/internal/gtest-param-util.h
# -- Installing: /usr/local/include/gtest/internal/gtest-filepath.h
# -- Installing: /usr/local/include/gtest/internal/gtest-port-arch.h
# -- Installing: /usr/local/include/gtest/internal/gtest-internal.h
# -- Installing: /usr/local/include/gtest/gtest-matchers.h
# -- Installing: /usr/local/include/gtest/gtest-assertion-result.h
# -- Installing: /usr/local/include/gtest/gtest-typed-test.h
# -- Installing: /usr/local/include/gtest/gtest_pred_impl.h
# -- Installing: /usr/local/include/gtest/gtest-message.h
# -- Installing: /usr/local/include/gtest/gtest.h
# -- Installing: /usr/local/include/gtest/gtest-printers.h
# -- Installing: /usr/local/include/gtest/gtest-test-part.h
# -- Installing: /usr/local/include/gtest/gtest_prod.h
# -- Installing: /usr/local/include/gtest/gtest-spi.h
# -- Installing: /usr/local/include/gtest/gtest-death-test.h
# -- Installing: /usr/local/include/gtest/gtest-param-test.h
# -- Installing: /usr/local/lib/libgtest.a
# -- Installing: /usr/local/lib/libgtest_main.a
# -- Installing: /usr/local/lib/pkgconfig/gtest.pc
# -- Installing: /usr/local/lib/pkgconfig/gtest_main.pc
```

</br>

### 2. Use `cmake` to setup the compile configuration and run unit test

```bash
# Make sure you're in the project root folder

#
# Create and cd into the `build` folder
#
mkdir build && cd build

#
# Generate make files into `build` folder
#
# Generate the `compile_commands.json` for `clangd_extensions` neovim plugin
#
cmake -DCMAKE_EXPORT_COMPILE_COMMANDS=1 \
    -DCMAKE_CXX_FLAGS="-std=gnu++17" \
    -DCMAKE_BUILD_TYPE=Debug \
    ..

# -- The C compiler identification is Clang 14.0.5
# -- The CXX compiler identification is Clang 14.0.5
# -- Detecting C compiler ABI info
# -- Detecting C compiler ABI info - done
# -- Check for working C compiler: /usr/bin/cc - skipped
# -- Detecting C compile features
# -- Detecting C compile features - done
# -- Detecting CXX compiler ABI info
# -- Detecting CXX compiler ABI info - done
# -- Check for working CXX compiler: /usr/bin/c++ - skipped
# -- Detecting CXX compile features
# -- Detecting CXX compile features - done
# -- Found GTest: /usr/local/lib/cmake/GTest/GTestConfig.cmake (found version "1.12.1")
# >>> CMAKE_SYSTEM_NAME: FreeBSD
# >>> CMAKE_BUILD_TYPE: Debug
# >>> CMAKE_C_COMPILER: /usr/bin/cc
# >>> CMAKE_C_FLAGS:
# >>> CMAKE_C_FLAGS_DEBUG: -g
# >>> CMAKE_C_FLAGS_RELEASE: -O3 -DNDEBUG
# >>> CMAKE_CXX_COMPILER: /usr/bin/c++
# >>> CMAKE_CXX_FLAGS: -std=gnu++17
# >>> CMAKE_CXX_FLAGS_DEBUG: -g
# >>> CMAKE_CXX_FLAGS_RELEASE: -O3 -DNDEBUG
# >>> GTest_FOUND: TRUE
# -- Configuring done
# -- Generating done
```

Pay attention to the following output:

```bash
# -- Found GTest: /usr/local/lib/cmake/GTest/GTestConfig.cmake (found version "1.12.1")
# >>> GTest_FOUND: TRUE
```

That means `cmake` find the installed `GoogleTest` and it knows where to find
the header files and link `GTest::gtest` and `GTest::gtest_main` libraries.

</br>

Run all unit test

```bash
cd build && make && ./c-utils
```

</br>


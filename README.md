# `c-utils`

This is my personal `C` utilities which contains the following modules:

- `Collection`: All kinds of list, stack and queue.

- `String`: Wrap and hide all `null-terminated` C-style string in `struct`,
hide the `null-terminated` detail and pointer, just deal with normal function
call.

    ```c
    /*
    * Create from empty
    */
    Str Str_from_empty();

    /*
    * Create from `char[]`
    */
    Str Str_from_arr(const char arr[]);

    /*
    * Create from `char*`
    */
    Str Str_from_str(const char *str);

    /*
    * Clone from given `Str` instance
    */
    Str Str_clone(const Str *src);

    /*
    * Push other `Str *` at the end
    */
    void Str_push_other(Str *self, const Str *other);

    /*
    * Push the given `char *` at the end
    */
    void Str_push_str(Str *self, const char *str_to_push);

    /*
    * Insert `Str *` to the beginning
    */
    void Str_insert_other_to_begin(Str *self, const Str *other);

    /*
    * Insert `char *` to the beginning
    */
    void Str_insert_str_to_begin(Str *self, const char *str_to_insert);


    /*
    * Insert `char *` at the given index
    */
    void Str_insert_at_index(Str *self, const char *str_to_insert,
                            usize index_to_insert);

    /*
    * Get back string length
    */
    usize Str_length(const Str *self);

    /*
    * Get back `char *`
    */
    const char *Str_as_str(const Str *self);

    /*
    * Find the given `char *` index, return `-1` if not found.
    */
    long Str_index_of(const Str *self, const char *str_to_find);

    /*
    * Find the given `char *` (case sensitive) index, return `-1` if not found.
    */
    long Str_index_of_case_sensitive(const Str *self, const char *str_to_find);

    /*
    * Check whether contain the given `char *` or not
    */
    bool Str_contains(const Str *self, char *str_to_check);

    /*
    * Reset  to empty string
    */
    void Str_reset_to_empty(Str *self);

    /*
    * Free allocated memory, reset length to 0 and internal buffer to `NULL`
    */
    void Str_free(Str *self);

    //
    // Examples
    //
    Str my_name = Str_from_str("Wison Ye:)");

    Str empty_str_1 = Str_from_str(NULL);
    Str empty_str_2 = Str_from_str("");

    Str clone_from_empty_str = Str_clone(&my_name);
    DEBUG_LOG(Main, StringTest, "clone_from_empty_str len: %lu, value: %s",
              Str_length(&clone_from_empty_str),
              Str_as_str(&clone_from_empty_str) == NULL
                  ? "NULL"
                  : Str_as_str(&clone_from_empty_str));

    // (D) [ Main ] > StringTest - clone_from_empty_str len: 8, value: Wison Ye⏎

    char temp_id[] = "123456789";
    char temp_id_2[] = {'A', 'B', 'C', 'D', '\0'};
    Str str_1 = Str_from_arr(temp_id);
    Str str_2 = Str_from_arr(temp_id_2);

    Str_free(&my_name);
    Str_free(&empty_str_1);
    Str_free(&empty_str_2);
    Str_free(&clone_from_empty_str);
    Str_free(&str_1);
    Str_free(&str_2);
    ```
    </br>

- `Log`: Handy logging implementation.

    - `LOG_VAR` macro, only available when `ENABLE_DEBUG_LOG ` is defined!!!

        Use to print the single variable's value, only for debugging purpose.

        ```c
        char *string_value = "Wison Ye";
        char char_value = 'c';
        u8 u8_value = 255;

        LOG_VAR(string_value);
        LOG_VAR(char_value);
        LOG_VAR(u8_value);

        LOG_VAR(sizeof(int));
        LOG_VAR(sizeof(long));

        // >>> string_value: Wison Ye
        // >>> char_value: c
        // >>> u8_value: 255
        // >>> sizeof(int): 4
        // >>> sizeof(long): 8
        ```

        </br>

    - `printf` liked formatted logger

        ```c
        #include "utils/log.h"
        #include "utils/string.h"

        Str my_str = Str_from_str("My name is Wison Ye");
        DEBUG_LOG(Main, main, "add(2, 3): %d", add(2, 3));
        DEBUG_LOG(Main, main, "2 + 2 :%d", 2 + 2);
        DEBUG_LOG(Main, main, "my_str value is: %s", Str_as_str(&my_str));
        INFO_LOG(Main, main, "my_str value is: %s", Str_as_str(&my_str));
        WARN_LOG(Main, main, "my_str value is: %s", Str_as_str(&my_str));
        ERROR_LOG(Main, main, "my_str value is: %s", Str_as_str(&my_str));

        // (D) [ Main ] > main - add(2, 3): 5
        // (D) [ Main ] > main - 2 + 2 :4
        // (D) [ Main ] > main - my_str value is: My name is Wison Ye
        // (I) [ Main ] > main - my_str value is: My name is Wison Ye
        // (W) [ Main ] > main - my_str value is: My name is Wison Ye
        // (E) [ Main ] > main - my_str value is: My name is Wison Ye⏎
        ```

        </br>

- `Vector`: Growable vector

</br>

### 0. `CMake` configurations

This project has 2 `cmake` setups for different purposes:

- `use_c_compiler_to_run_main/CMakeLists.txt`

   Use `C` compiler to compile `main.c` and then use `memory leaking tools` to
   check memory leaking issue on the pure `C` binary. Otherwise, if I use `CPP`
   compiler to compile the binary which links to `gtest`, then faulty memory
   leaking is detected!!!

   </br>


- `use_cpp_compiler_to_run_googletest/CMakeLists.txt`

    As `GoogleTest` only work for `CPP`, that's why you need the separated `CPP`
    compilation setup.

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

### 2. `cmake` setup and run

#### 2.1 Use `C` compiler to compile `main.c`

```bash
# Make sure you're in the project root folder
./configure_c.sh
```

</br>

It Generates everything needs into `build_c` folder and the
`build/compile_commands.json` for `clangd_extensions` neovim plugin

</br>

Compile and run:

```bash
./build_and_run_c.sh
```

</br>

Memory leak check:

```bash
valgrind --leak-check=full --show-reachable=yes build_c/c-utils

# ==58532== Memcheck, a memory error detector
# ==58532== Copyright (C) 2002-2022, and GNU GPL'd, by Julian Seward et al.
# ==58532== Using Valgrind-3.20.0 and LibVEX; rerun with -h for copyright info
# ==58532== Command: build_c/c-utils
# ==58532==
# ==58532==
# ==58532== HEAP SUMMARY:
# ==58532==     in use at exit: 0 bytes in 0 blocks
# ==58532==   total heap usage: 4 allocs, 4 frees, 48 bytes allocated
# ==58532==
# ==58532== All heap blocks were freed -- no leaks are possible
# ==58532==
# ==58532== For lists of detected and suppressed errors, rerun with: -s
# ==58532== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)
```

</br>


#### 2.2 Use `CPP` compiler to compile `main.cpp`

```bash
# Make sure you're in the project root folder
./configure_cpp.sh
```

It Generates everything needs into `build_unit_test` folder and the
`build/compile_commands.json` for `clangd_extensions` neovim plugin

</br>

Pay attention to the following output:

```bash
# -- Found GTest: /usr/local/lib/cmake/GTest/GTestConfig.cmake (found version "1.12.1")
# >>> GTest_FOUND: TRUE
```

That means `cmake` find the installed `GoogleTest` and it knows where to find
the header files and link `GTest::gtest` and `GTest::gtest_main` libraries.

</br>

Compile and run all unit test:

```bash
./build_and_run_unit_test.sh

# [100%] Linking CXX executable c-utils-unit-test
# [100%] Built target c-utils-unit-test
# [==========] Running 3 tests from 1 test suite.
# [----------] Global test environment set-up.
# [----------] 3 tests from SingleLinkList
# [ RUN      ] SingleLinkList.CreateEmptyList
# [       OK ] SingleLinkList.CreateEmptyList (0 ms)
# [ RUN      ] SingleLinkList.IntegerList
# [       OK ] SingleLinkList.IntegerList (0 ms)
# [ RUN      ] SingleLinkList.DoubleList
# [       OK ] SingleLinkList.DoubleList (0 ms)
# [----------] 3 tests from SingleLinkList (0 ms total)
# 
# [----------] Global test environment tear-down
# [==========] 3 tests from 1 test suite ran. (0 ms total)
# [  PASSED  ] 3 tests.
```

</br>

#### 3. How to preview preprocess step source code

It's beneficial if you can print out the source code content after the
preprocessor step (but before throwing it into the compiler)

```bash
# `-D`: Use to define macros
# `-E`: Run the preprocessor stage.
clang -E -D ENABLE_DEBUG_LOG src/main.c | bat
```

</br>


#### 4. How to print all supported macros on current computer and OS

```bash
clang -dM -E - < /dev/null
```

</br>

Also, you can use it to confirm whether the parituclar OS macro defines or not:

```bash
clang -dM -E - < /dev/null | rg BSD
#define __FreeBSD__ 14
#define __FreeBSD_cc_version 1400001
```

</br>

Support OS:

|OPERATING SYSTEM | MACRO PRESENT | NOTES
| --------------- | ------------- | ----- |
|Windows 32 bit + 64 bit | _WIN32 | for all Windows OS ||
|Windows 64 bit | _WIN64 | Only for 64 bit Windows ||
|Apple | __APPLE__ | for all Apple OS|
|Apple | __MACH__ | alternative to above|
|iOS embedded | TARGET_OS_EMBEDDED | include TargetConditionals.h|
|iOS stimulator | TARGET_IPHONE_SIMULATOR | include TargetConditionals.h|
|iPhone | TARGET_OS_IPHONE | include TargetConditionals.h|
|MacOS | TARGET_OS_MAC | include TargetConditionals.h|
|Android | __ANDROID__ | subset of linux|
|Unix based OS | __unix__ ||
|Linux | __linux__ | subset of unix|
|POSIX based | _POSIX_VERSION | Windows with Cygwin|
|Solaris | __sun | |
|HP UX | __hpux | |
|BSD | BSD | all BSD flavors|
|DragonFly BSD | __DragonFly__ | |
|FreeBSD | __FreeBSD__ | |
|NetBSD | __NetBSD__ | |
|OpenBSD | __OpenBSD__ | |


#include "./file_test.h"

#include <errno.h>
#include <pwd.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <unity.h>

#include "../../utils/file.h"
#include "../../utils/heap_string.h"

void test_file_open_should_fail(void) {
    char *test_filename = (char *)"/file-that-not-exists.txt";
    defer_file(file)    = File_open(test_filename, FM_READ_ONLY);

    TEST_ASSERT_EQUAL_STRING(File_get_filename(file), test_filename);
    TEST_ASSERT_EQUAL(File_is_open_successfully(file), false);

    TEST_ASSERT_NOT_NULL(File_get_error(file));
    TEST_ASSERT_EQUAL_STRING(File_get_error(file), "No such file or directory");

    TEST_ASSERT_NULL(File_get_data(file));
    TEST_ASSERT_EQUAL_UINT(File_get_size(file), 0);
}

void test_file_open_should_success(void) {
    struct passwd *pw       = getpwuid(getuid());
    const char *home_folder = pw->pw_dir;
    defer_file(file)        = File_open(home_folder, FM_READ_ONLY);

    TEST_ASSERT_EQUAL_STRING(File_get_filename(file), home_folder);
    TEST_ASSERT_EQUAL(File_is_open_successfully(file), true);

    TEST_ASSERT_NULL(File_get_error(file));
    TEST_ASSERT_NULL(File_get_data(file));
    TEST_ASSERT_GREATER_THAN(0, File_get_size(file));
}

void test_file_read_should_success(void) {
    char cwd[PATH_MAX];
    if (getcwd(cwd, sizeof(cwd)) != NULL) {
        defer_string(test_filename_str) = HS_from_str(cwd);
        HS_push_str(test_filename_str, "/compile_commands.json");

        // printf("Current working dir: %s\n", cwd);
        // printf("\n>>> test_filename_str: %s", HS_as_str(test_filename_str));

        defer_file(test_file) =
            File_open(HS_as_str(test_filename_str), FM_READ_ONLY);
        File_load_into_buffer(test_file);

        TEST_ASSERT_EQUAL_STRING(File_get_filename(test_file),
                                 HS_as_str(test_filename_str));
        TEST_ASSERT_EQUAL(File_is_open_successfully(test_file), true);

        TEST_ASSERT_NULL(File_get_error(test_file));
        TEST_ASSERT_NOT_NULL(File_get_data(test_file));
        TEST_ASSERT_GREATER_THAN(0, File_get_size(test_file));

        // File_load_into_buffer(test_file);
        // printf("\n>>> test_file content: %s", File_get_data(test_file));
    }
}

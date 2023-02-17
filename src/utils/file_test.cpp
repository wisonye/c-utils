
#include <gtest/gtest.h>

extern "C" {
#include <errno.h>
#include <pwd.h>
#include <stdio.h>
#include <unistd.h>

#include "file.h"
#include "string.h"
}

TEST(File, OpenShouldFail) {
    char *test_filename = (char *)"/file-that-not-exists.txt";
    SMART_FILE(file) = File_open(test_filename, FM_READ_ONLY);

    ASSERT_EQ(strcmp(File_get_filename(file), test_filename), 0);
    ASSERT_EQ(File_is_open_successfully(file), false);

    ASSERT_NE(File_get_error(file), nullptr);
    ASSERT_EQ(strcmp(File_get_error(file), "No such file or directory"), 0);

    ASSERT_EQ(File_get_data(file), nullptr);
    ASSERT_EQ(File_get_size(file), 0);
}

TEST(File, OpenShouldSuccess) {
    struct passwd *pw = getpwuid(getuid());
    const char *home_folder = pw->pw_dir;
    SMART_FILE(file) = File_open(home_folder, FM_READ_ONLY);

    ASSERT_EQ(strcmp(File_get_filename(file), home_folder), 0);
    ASSERT_EQ(File_is_open_successfully(file), true);

    ASSERT_EQ(File_get_error(file), nullptr);
    ASSERT_EQ(File_get_data(file), nullptr);
    ASSERT_GT(File_get_size(file), 0);
}

TEST(File, ReadShouldSuccess) {
    char cwd[PATH_MAX];
    if (getcwd(cwd, sizeof(cwd)) != NULL) {
        // printf("Current working dir: %s\n", cwd);
        SMART_STRING(test_filename_str) = Str_from_str(cwd);
        Str_push_str(test_filename_str, "/CTestTestfile.cmake");

        SMART_FILE(test_file) =
            File_open(Str_as_str(test_filename_str), FM_READ_ONLY);
        File_load_into_buffer(test_file);

        ASSERT_EQ(
            strcmp(File_get_filename(test_file), Str_as_str(test_filename_str)),
            0);
        ASSERT_EQ(File_is_open_successfully(test_file), true);

        ASSERT_EQ(File_get_error(test_file), nullptr);
        ASSERT_NE(File_get_data(test_file), nullptr);
        ASSERT_GT(File_get_size(test_file), 0);
    }
}

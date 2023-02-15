
#include <gtest/gtest.h>

extern "C" {
#include <errno.h>
#include <pwd.h>
#include <stdio.h>

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
}

TEST(File, OpenShouldSuccess) {
    struct passwd *pw = getpwuid(getuid());
    const char *home_folder = pw->pw_dir;
    SMART_FILE(file) = File_open(home_folder, FM_READ_ONLY);

    ASSERT_EQ(strcmp(File_get_filename(file), home_folder), 0);
    ASSERT_EQ(File_is_open_successfully(file), true);

    ASSERT_EQ(File_get_error(file), nullptr);
}

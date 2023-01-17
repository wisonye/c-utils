#include <gtest/gtest.h>

extern "C" {
#include "single_link_list.h"
}

TEST(SingleLinkList, CreateEmptyList) {
    // EXPECT_EQ(get_random_int(), 888);
    ASSERT_EQ(get_random_int(), 999);
}

TEST(SingleLinkList, CreateCustomStructList) {
    // EXPECT_EQ(get_random_int(), 888);
    ASSERT_EQ(get_random_int(), 999);
}

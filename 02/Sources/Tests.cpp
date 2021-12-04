#include <gtest/gtest.h>
#include <string>
#include "Source.h"

typedef unsigned int uint;

TEST(RemoveDups, ExampleOne) {
    char test1[] = "AAA BBB AAA";
    const char answer1[] = "A B A";
    RemoveDups(test1);
    EXPECT_STREQ(test1, answer1);
}

TEST(RemoveDups, ExampleTwo) {
    char test1[] = "A B A";
    const char answer1[] = "A B A";
    RemoveDups(test1);
    EXPECT_STREQ(test1, answer1);
}

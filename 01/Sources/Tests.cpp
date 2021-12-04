#include <gtest/gtest.h>
#include <bitset>
#include <limits>
#include <string>
#include "Source.h"

typedef unsigned int uint;

TEST(IntToBinary, IntMinMax) {
    EXPECT_STREQ(int_to_string_binary(std::numeric_limits<int>::max()), "01111111111111111111111111111111");
    EXPECT_STREQ(int_to_string_binary(std::numeric_limits<int>::min()), "10000000000000000000000000000000");
}

TEST(IntToBinary, IntOne) {
    EXPECT_STREQ(int_to_string_binary(1), "00000000000000000000000000000001");
}

TEST(IntToBinary, IntMinOne) {
    EXPECT_STREQ(int_to_string_binary(-1), "11111111111111111111111111111111");
}

TEST(IntToBinary, IntZero) {
    EXPECT_STREQ(int_to_string_binary(0), "00000000000000000000000000000000");
}

TEST(IntToBinary, IntZeroLib) {
    EXPECT_STREQ(int_to_string_binary(0), std::bitset<std::numeric_limits<uint>::digits>(0).to_string().data());
}

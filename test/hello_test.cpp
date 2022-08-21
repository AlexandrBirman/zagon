#include <gtest/gtest.h>
#include "hello.h"

TEST(HelloTest, say) {
    Hello h;
    EXPECT_EQ("hello", h.say());
}
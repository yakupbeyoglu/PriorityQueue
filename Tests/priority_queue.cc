
#include "../Source/priority_queue.hpp"

#include <gtest/gtest.h>

#undef ASSERT_FALSE
#undef ASSERT_ALL

TEST(initial_test, BasicAssertions) {
  yb::priority_queue queue;
  EXPECT_EQ(3, 2 + 1);
}

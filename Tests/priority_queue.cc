
#include "../Source/priority_queue.hpp"

#include <gtest/gtest.h>

#undef ASSERT_FALSE
#undef ASSERT_ALL

template <typename T, typename Comp>
bool isPriorityQueueSorted(yb::priority_queue<T, Comp> &queue) {
  for (std::size_t i = 1; i < queue.size(); ++i) {
    if (queue.comparator(queue[i], queue[i - 1])) {
      return false;  // Not prioritized
    }
  }
  return true;  // Prioritized
}

TEST(DefaultConstructor, BasicAssertions) {
  yb::priority_queue<int> queue;
  EXPECT_TRUE(queue.empty());
  EXPECT_EQ(queue.size(), 0);
}

TEST(CopyConstructor, BasicAssertions) {
  yb::priority_queue<int> queue;

  queue.emplace(10);
  queue.emplace(5);
  queue.emplace(20);

  yb::priority_queue<int> copiedQueue(queue);
  EXPECT_EQ(copiedQueue.size(), queue.size());
  EXPECT_EQ(copiedQueue.top(), queue.top());
  EXPECT_EQ(copiedQueue.empty(), queue.empty());
  EXPECT_TRUE(isPriorityQueueSorted(copiedQueue));
}

// Test copy assignment operator
TEST(CopyAssignmentOperator, BasicAssertions) {
  yb::priority_queue<int> queue;
  queue.emplace(10);
  queue.emplace(5);
  queue.emplace(20);

  yb::priority_queue<int> copiedQueue;
  copiedQueue = queue;
  EXPECT_EQ(copiedQueue.size(), queue.size());
  EXPECT_EQ(copiedQueue.top(), queue.top());
  EXPECT_EQ(copiedQueue.empty(), queue.empty());
  EXPECT_TRUE(isPriorityQueueSorted(copiedQueue));
}

// Test move constructor
TEST(MoveConstructor, BasicAssertions) {
  yb::priority_queue<int, std::greater<int>> queue;

  queue.emplace(10);
  queue.emplace(5);
  queue.emplace(20);

  yb::priority_queue<int, std::greater<int>> movedQueue(std::move(queue));
  EXPECT_EQ(movedQueue.size(), 3);
  EXPECT_TRUE(queue.empty());
  EXPECT_TRUE(isPriorityQueueSorted(movedQueue));
}

// Test move assignment operator
TEST(MoveAssignmentOperator, BasicAssertions) {
  yb::priority_queue<int> queue;
  queue.emplace(10);
  queue.emplace(5);
  queue.emplace(20);

  yb::priority_queue<int> movedQueue;
  movedQueue = std::move(queue);
  EXPECT_EQ(movedQueue.size(), 3);
  EXPECT_TRUE(queue.empty());
  EXPECT_TRUE(isPriorityQueueSorted(movedQueue));
}

// Test emplace function
TEST(PriorityQueueTest, Emplace) {
  yb::priority_queue<int, std::greater<int>> queue;

  queue.emplace(10);
  queue.emplace(5);
  queue.emplace(20);

  EXPECT_EQ(queue.size(), 3);
  EXPECT_TRUE(isPriorityQueueSorted(queue));
}

// Test emplace with initializer list
TEST(PriorityQueueTest, EmplaceInitializerList) {
  yb::priority_queue<int> queue;
  queue.emplace({10, 5, 20});

  EXPECT_EQ(queue.size(), 3);
  EXPECT_TRUE(isPriorityQueueSorted(queue));
}

// Test pop_back function
TEST(PriorityQueueTest, PopBack) {
  yb::priority_queue<int> queue;
  queue.emplace(10);
  queue.emplace(5);
  queue.emplace(20);
  queue.pop_back();

  EXPECT_EQ(queue.size(), 2);
  EXPECT_TRUE(isPriorityQueueSorted(queue));
}

// Test erase function
TEST(PriorityQueueTest, Erase) {
  yb::priority_queue<int> queue;
  queue.emplace(10);
  queue.emplace(5);
  queue.emplace(20);

  queue.erase(1);  // Erase element at index 1

  EXPECT_EQ(queue.size(), 2);
  EXPECT_TRUE(isPriorityQueueSorted(queue));
}

// Test top function
TEST(PriorityQueueTest, Top) {
  yb::priority_queue<int> queue;
  queue.emplace(10);
  queue.emplace(5);
  queue.emplace(20);

  EXPECT_EQ(queue.top(), 5);
}

// Test size function
TEST(PriorityQueueTest, Size) {
  yb::priority_queue<int> queue;

  queue.emplace(10);
  queue.emplace(5);
  queue.emplace(20);

  EXPECT_EQ(queue.size(), 3);
}

// Test empty function
TEST(PriorityQueueTest, Empty) {
  yb::priority_queue<int> queue;
  EXPECT_TRUE(queue.empty());

  queue.emplace(10);
  queue.emplace(5);
  queue.emplace(20);

  EXPECT_FALSE(queue.empty());
}

// Test swap function
TEST(PriorityQueueTest, Swap) {
  yb::priority_queue<int> queue;

  queue.emplace(10);
  queue.emplace(5);
  queue.emplace(20);

  yb::priority_queue<int> otherQueue;
  otherQueue.emplace(30);
  otherQueue.emplace(15);

  swap(queue, otherQueue);

  EXPECT_EQ(queue.size(), 2);
  EXPECT_EQ(otherQueue.size(), 3);
  EXPECT_TRUE(isPriorityQueueSorted(otherQueue));
  EXPECT_TRUE(isPriorityQueueSorted(queue));
}

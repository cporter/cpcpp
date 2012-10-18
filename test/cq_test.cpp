

#include "../include/ConcurrentQueue.hpp"
#include <gtest/gtest.h>

typedef cpcpp::ConcurrentQueue<int> iq_t;

TEST (CQTest, SingleThread)
{ iq_t foo;
  for (int i = 0; i < 10; ++i)
    foo . Enqueue (i);

  EXPECT_EQ (10, foo . Count ());

  for (int i = 0; i < 10; ++i)
    { int x = foo . Dequeue ();
      EXPECT_EQ (i, x) << "Order should be maintained";
    }

  EXPECT_EQ (0, foo . Count ());
}

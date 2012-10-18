

#include <cpcpp/ConcurrentQueue.hpp>
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

struct consumer {
  iq_t *q;
  int *count;
  consumer (iq_t *_q, int *c)  :  q (_q), count (c) {}
  void operator()() {
    while (true) {
      int x = q -> Dequeue ();
      if (x < 0)
	break;
      else *count += x;
    }
  }
};

TEST (CQTest, MultipleThreads)
{ iq_t foo;
  std::vector<boost::thread*> threads;

  const size_t N_THREADS = 10;
  const size_t N_INPUT = 1000;

  std::vector<int> counts (N_THREADS);
  for (int i = 0; i < N_THREADS; ++i)
    threads . push_back (new boost::thread (consumer (&foo, &counts[i])));
  
  int expected = 0;
  for (int i = 0; i < N_INPUT; ++i)
    { foo . Enqueue (i);
      expected += i;
    }

  for (int i = 0; i < N_THREADS; ++i)
    foo . Enqueue (-1);

  int total = 0;
  for (int i = 0; i < N_THREADS; ++i)
    { threads[i] -> join ();
      delete threads[i];
      total += counts[i];
    }

  int zeros = 0;
  for (int i = 0; i < N_THREADS; ++i)
    if (0 == counts[i])
      ++zeros;

  EXPECT_GT (N_THREADS - 1, zeros)
    << "The work shouldn't have all been done by one thread....";
  EXPECT_EQ (expected, total);
}


#ifndef __CONCURRENT_QUEUE_HPP__
#define __CONCURRENT_QUEUE_HPP__

#include <boost/thread.hpp>


/// A very, very simple queue for use in a multi-threaded environment
template <typename T>
class ConcurrentQueue {
private:
  std::queue<T> q;
  mutable boost::mutex mutex;
  boost::condition_variable cond;
  
public:
  /// Add an element to the front of the queue
  void Enqueue(T t);
  /// Remove an element from the back of the queue. Blocks if queue is empty
  T Dequeue();
  /// How many things are currently in the queue?
  /// Note: this does not account for any current blockers
  const size_t Count() const;
};

template<typename T>
void ConcurrentQueue<T>::Enqueue(T t)
{ boost::mutex::scoped_lock lock(mutex);
  q . push(t);
  lock . unlock();
  cond . notify_one();
}

template<typename T>
T ConcurrentQueue<T>::Dequeue()
{ boost::mutex::scoped_lock lock(mutex); 
  while( 0 == q . size() )
    cond . wait (lock);
  T tmp = q . front();
  q . pop();
  return tmp;
}

template<typename T>
const size_t ConcurrentQueue<T>::Count() const
{ boost::mutex::scoped_lock lock(mutex);
  return q . size();
}

#endif //!__CONCURRENT_QUEUE_HPP__

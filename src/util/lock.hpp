#ifndef _HADOOP_UTIL_LOCK_HPP_
#define _HADOOP_UTIL_LOCK_HPP_

#include <pthread.h>

// really simple implementation for thread compatibility layer

namespace hadoop {
namespace util {

class Lock {
  friend class Condition;
public:
  Lock() { pthread_mutex_init(&m, NULL); }
  ~Lock() { pthread_mutex_destroy(&m); }
  int lock() { return pthread_mutex_lock(&m); }
  int unlock() { return pthread_mutex_unlock(&m); }

protected:
  pthread_mutex_t m;
};

class ScopedLock {
public:
  explicit ScopedLock(Lock& lk) : l(&lk){ l->lock(); }
  ~ScopedLock() { l->unlock(); }

private:
  Lock *l;
};

} // namespace util
} // namespace hadoop

#endif /* Not def: _HADOOP_UTIL_LOCK_HPP_ */

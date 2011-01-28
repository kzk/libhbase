#ifndef _HADOOP_UTIL_COND_HPP_
#define _HADOOP_UTIL_COND_HPP_

#include "lock.hpp"
#include <pthread.h>

namespace hadoop {
namespace util {

class Condition {
  Condition() {
    pthread_cond_init(&cond, NULL);
  }
  ~Condition() {
    pthread_cond_destroy(&cond);
  }

  void wait(Lock& lk) {
    pthread_cond_wait(&cond, &lk.m);
  }
  void notify() {
    pthread_cond_signal(&cond);
  }
  void notify_all() {
    pthread_cond_broadcast(&cond);
  }

private:
  pthread_cond_t cond;
};

} // namespace util
} // namespace hadoop

#endif /* Not def: _HADOOP_UTIL_COND_HPP_ */


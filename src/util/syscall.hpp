#ifndef _HADOOP_UTIL_SYSCALL_HPP_
#define _HADOOP_UTIL_SYSCALL_HPP_

#include <errno.h>

#define CALL_SYSCALL3(result, expr, check)			      \
  do {                                                                \
    (result) = (expr);						      \
    if ((check) && errno == EINTR) {				      \
      /* retry */;						      \
    } else {							      \
      break;							      \
    }								      \
  } while (1)

#define CALL_SYSCALL(result, expr)              \
  CALL_SYSCALL3(result, (expr), (result < 0))

#ifndef NO_INTR
#define NO_INTR(result, expr)			\
  CALL_SYSCALL(result, expr)
#endif

#endif

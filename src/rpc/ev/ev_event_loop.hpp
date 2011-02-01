#ifndef _HADOOP_RPC_EV_EVENT_LOOP_HPP_
#define _HADOOP_RPC_EV_EVENT_LOOP_HPP_

#include <ev.h>

namespace hadoop {
namespace rpc {
namespace ev {

/**
 * EventLoop implementation by libev (http://cvs.schmorp.de/libev/)
 */
class EvEventLoop {
public:
  EvEventLoop();
  virtual ~EvEventLoop();

  virtual void run();
  virtual void runOnce();

protected:
  struct ev_loop *loop;
};

} // namespace ev
} // namespace rpc
} // namespace hadoop

#endif /* Not def: _HADOOP_RPC_EV_EVENT_LOOP_HPP_ */

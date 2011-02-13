#ifndef _HADOOP_RPC_EV_EVENT_LOOP_HPP_
#define _HADOOP_RPC_EV_EVENT_LOOP_HPP_

#include "rpc/event_loop.hpp"
#include "rpc/libev/ev_transport.hpp"
#include <ev.h>

namespace hadoop {
namespace rpc {
namespace ev {

/**
 * EventLoop implementation by libev (http://cvs.schmorp.de/libev/)
 */
class EvEventLoop : public hadoop::rpc::EventLoop {
public:
  EvEventLoop();
  virtual ~EvEventLoop();

  virtual void run();
  virtual void runOnce();
  virtual Transport* openTransport(const std::string& addr) {
    return new EvTransport(this, addr);
  }

  struct ev_loop* getLoop() const { return evloop; }

protected:
  struct ev_loop *evloop;
};

} // namespace ev
} // namespace rpc
} // namespace hadoop

#endif /* Not def: _HADOOP_RPC_EV_EVENT_LOOP_HPP_ */

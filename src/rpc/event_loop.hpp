#ifndef _HADOOP_RPC_EVENTLOOP_HPP_
#define _HADOOP_RPC_EVENTLOOP_HPP_

#include <string>

namespace hadoop {
namespace rpc {
class Transport;

class EventLoop {
public:
  EventLoop() {}
  virtual ~EventLoop() {}

  virtual void run() = 0;
  virtual void runOnce() = 0;
  virtual Transport* openTransport(const std::string& addr) = 0;
};

EventLoop* CreateEventLoop(const std::string& type);

} // namespace rpc
} // namespace hadoop

#endif /* Not def: _HADOOP_RPC_EVENTLOOP_HPP_ */

#ifndef _HADOOP_RPC_EVENTLOOP_HPP_
#define _HADOOP_RPC_EVENTLOOP_HPP_

namespace hadoop {
namespace rpc {
class Transport;

class EventLoop {
public:
  EventLoop() {}
  virtual ~EventLoop() {}

  virtual void run() = 0;
  virtual void runOnce() = 0;
  virtual Transport* openTransport() = 0;
};

} // namespace rpc
} // namespace hadoop

#endif /* Not def: _HADOOP_RPC_EVENTLOOP_HPP_ */

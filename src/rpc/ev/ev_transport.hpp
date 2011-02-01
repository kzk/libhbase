#ifndef _HADOOP_RPC_EV_TRANSPORT_HPP_
#define _HADOOP_RPC_EV_TRANSPORT_HPP_

#include "rpc/transport.hpp"

namespace hadoop {
namespace rpc {
namespace ev {

class EvTransport : public hadoop::rpc::Transport {
public:
  EvTransport(EventLoop* loop, const std::string& addr);
  virtual ~EvTransport();

  virtual int open();
  virtual void onRead(void* buf);
  virtual void onMessage(void* msg);
  virtual void close();

protected:
  int fd;
};

} // namespace ev
} // namespace rpc
} // namespace hadoop

#endif /* Not def: _HADOOP_RPC_EV_TRANSPORT_HPP_ */

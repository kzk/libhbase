#ifndef _HADOOP_RPC_EV_TRANSPORT_HPP_
#define _HADOOP_RPC_EV_TRANSPORT_HPP_

#include "rpc/transport.hpp"
#include <vector>
#include <deque>

namespace hadoop {
namespace rpc {
namespace ev {
class EvSocket;

class EvTransport : public hadoop::rpc::Transport {
public:
  EvTransport(EventLoop* loop, const std::string& addr);
  virtual ~EvTransport();

  virtual int open();
  virtual int sendMessage(void* msg, size_t msglen);
  virtual void onRead(void* buf);
  virtual void onMessage(void* msg);
  virtual void close();

protected:
  int tryConnect();
  int sendPendingMessages();

protected:
  EvSocket* sock;
  bool connected;
  std::deque<std::pair<void*, size_t> > pendingMessages;
};

} // namespace ev
} // namespace rpc
} // namespace hadoop

#endif /* Not def: _HADOOP_RPC_EV_TRANSPORT_HPP_ */

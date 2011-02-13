#ifndef _HADOOP_RPC_CLIENT_HPP_
#define _HADOOP_RPC_CLIENT_HPP_

#include <string>
#include "rpc/event_loop.hpp"

namespace hadoop {
namespace rpc {
class Transport;

class Client {
public:
  Client(const std::string& addr, EventLoop* loop);
  ~Client();

  int callAsync(void* msg, size_t msglen);
  void close();

protected:
  std::string addr;
  EventLoop* loop;
  Transport* tran;
};

} // namespace rpc
} // namespace hadoop

#endif /* Not def: _HADOOP_RPC_CLIENT_HPP_ */

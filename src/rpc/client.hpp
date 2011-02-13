#ifndef _HADOOP_RPC_CLIENT_HPP_
#define _HADOOP_RPC_CLIENT_HPP_

#include <string>
#include "util/lock.hpp"
#include "rpc/event_loop.hpp"

namespace hadoop {
namespace rpc {
class Transport;

/**
 * The client interface of RPC (Remote Procedure Call) mechanism.
 * An example Client class usage is like below:
 *
 * EventLoop* loop = CreateEventLoop("libev");
 * Client* cln = new Client("localhost:1985", loop);
 * cln->callAsync(msg, msglen);
 * cln->close();
 * delete cln;
 * delete loop;
 *
 */
class Client {
public:
  Client(const std::string& addr, EventLoop* loop);
  ~Client();

  int callAsync(void* msg, size_t msglen);
  void close();

protected:
  hadoop::util::Lock cln_lk;
  std::string addr;
  EventLoop* loop;
  Transport* tran;
};

} // namespace rpc
} // namespace hadoop

#endif /* Not def: _HADOOP_RPC_CLIENT_HPP_ */

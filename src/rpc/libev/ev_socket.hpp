#ifndef _HADOOP_RPC_EV_SOCKET_HPP_
#define _HADOOP_RPC_EV_SOCKET_HPP_

#include <ev.h>
#include <string>

namespace hadoop {
namespace rpc {
namespace ev {
class EvSocketWatcher;
class EvEventLoop;

class EvSocket {
public:
  EvSocket();
  ~EvSocket();

  int open(const std::string& addr);
  int send(void* msg, size_t msglen);
  int attach(EvEventLoop* loop);
  void close();

public:
  // 2011/02/13 Kazuki Ohta <kazuki.ohta@gmail.com>
  // public member for the callback function from libev.
  int onRead(int revents);

protected:
  int fd;
  struct EvEventLoop* loop;
  struct EvSocketWatcher* watcher;
};

} // namespace ev
} // namespace rpc
} // namespace hadoop

#endif /* Not def: _HADOOP_RPC_EV_SOCKET_HPP_ */

#ifndef _HADOOP_RPC_EV_SOCKET_HPP_
#define _HADOOP_RPC_EV_SOCKET_HPP_

#include <ev.h>
#include <string>

namespace hadoop {
namespace rpc {
namespace ev {
class EvSocketWatcher;

class EvSocket {
public:
  EvSocket();
  ~EvSocket();

  int open(const std::string& addr);
  int attach(struct ev_loop* loop);
  int onRead(int revents);
  void close();

protected:
  int fd;
  struct ev_loop* loop;
  struct EvSocketWatcher* watcher;
};

} // namespace ev
} // namespace rpc
} // namespace hadoop

#endif /* Not def: _HADOOP_RPC_EV_SOCKET_HPP_ */

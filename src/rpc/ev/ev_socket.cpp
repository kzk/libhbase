#include "rpc/ev/ev_socket.hpp"

#include <cassert>
#include <vector>

using namespace std;

namespace hadoop {
namespace rpc {
namespace ev {

struct EvSocketWatcher {
  ev_io io;
  void* ptr;
};

namespace {
void read_cb(struct ev_loop* loop, ev_io* watcher, int revents)
{
  assert(watcher != NULL);
  struct EvSocketWatcher* w = (struct EvSocketWatcher*)watcher;
  EvSocket* sock = (EvSocket*)w->ptr;
  sock->onRead(revents);
}
} // namespace

EvSocket::EvSocket()
  : watcher(new EvSocketWatcher())
{
  watcher->ptr = this;
}

EvSocket::~EvSocket()
{
  assert(watcher == NULL);
}

int EvSocket::open(const string& addr)
{
  string::size_type idx = addr.find(':');
  if (idx == string::npos) return -1;
  string host = addr.substr(0, idx);
  int port = atoi(addr.substr(idx+1).c_str());;
}

int EvSocket::attach(struct ev_loop* loop)
{
  assert(fd >= 0);
  ev_io_init(&watcher->io, read_cb, fd, EV_READ);
  ev_io_start(loop, &watcher->io);
  return 0;
}

int EvSocket::onRead(int revents)
{
  if(EV_ERROR & revents) return -1;
  return 0;
}

void EvSocket::close()
{
  ev_io_stop(loop, &watcher->io);
  if (watcher) delete watcher;
  watcher = NULL;
}

} // namespace ev
} // namespace rpc
} // namespace hadoop

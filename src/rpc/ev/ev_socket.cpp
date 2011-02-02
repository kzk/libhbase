#include "rpc/ev/ev_socket.hpp"
#include "util/dns.hpp"
#include "util/syscall.hpp"

#include <signal.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/uio.h>
#include <netinet/in.h>
#include <netinet/tcp.h>
#include <arpa/inet.h>
#include <cassert>
#include <iostream>
#include <vector>

using namespace std;
using namespace hadoop::util;

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
  int r;
  string::size_type idx = addr.find(':');
  if (idx == string::npos) return -1;
  string host = addr.substr(0, idx);
  string port = addr.substr(idx+1);
  if (host.empty() || atoi(port.c_str()) < 0)
    return -1;

  vector<IPv4Addr> addrs;
  r = DNSResolver::resolve(host, port, addrs);
  if (r != 0) return -1;

  int sock = -1;
  NO_INTR(sock, ::socket(PF_INET, SOCK_STREAM, 0));
  if (sock < 0)
    return -1;

#if defined(__linux__)
  // TCP nodelay, latency over bandwidth
  int one = 1;
  NO_INTR(r, setsockopt(sock, SOL_TCP, TCP_NODELAY, (char *)&one, sizeof(int)));
  if (r != 0)
    return -1;
#endif

  // 2011/02/03 Kazuki Ohta <kazuki.ohta@gmail.com>
  // TODO: non-blocking connect(2), to hide the 3-way handshake latency.

  bool succeed = false;
  for (unsigned int i = 0; addrs.size(); i++) {
    sockaddr_in addrin = {};
    addrin.sin_family = PF_INET;
    addrin.sin_addr.s_addr = inet_addr(addrs[i].toString().c_str());
    addrin.sin_port = htons(atoi(port.c_str()));

    NO_INTR(r, ::connect(sock, (sockaddr*)&addrin, sizeof(addrin)));
    if (r == 0) {
      succeed = true;
      break;
    }
  }
  if (succeed) fd = sock;
  return 0;
}

int EvSocket::attach(struct ev_loop* l)
{
  assert(fd >= 0);
  loop = l;
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
  if (loop)
    ev_io_stop(loop, &watcher->io);

  if (watcher) delete watcher;
  watcher = NULL;

  if (fd >= 0) ::close(fd);
  fd = -1;
}

} // namespace ev
} // namespace rpc
} // namespace hadoop

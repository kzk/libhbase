#include "rpc/libev/ev_transport.hpp"
#include "rpc/libev/ev_socket.hpp"
#include "rpc/libev/ev_transport.hpp"

#include <ev.h>
#include <cassert>
#include <vector>
#include <iostream>

using namespace std;

namespace hadoop {
namespace rpc {
namespace ev {
EvTransport::EvTransport(EventLoop* loop, const string& addr)
  : Transport(loop, addr),
    sock(NULL), connected(false)
{
}

EvTransport::~EvTransport()
{
}

int EvTransport::open()
{
  EvSocket *s = new EvSocket();
  if (s == NULL) return -1;
  sock = s;
  Transport::open();
  return 0;
}

int EvTransport::sendMessage(void* msg, size_t msglen)
{
  assert(sock != NULL);

  int r;
  if (!connected) {
    r = tryConnect();
    if (r != 0) return -1;
  }

  pendingMessages.push_back(make_pair(msg, msglen));
  sendPendingMessages();
  return 0;
}

int EvTransport::tryConnect()
{
  int r;
  r = sock->open(addr);
  if (r != 0) return -1;

  // 2011/02/13 Kazuki Ohta <kazuki.ohta@gmail.com>
  // Now we're using blocking connect(2). Will be changed to use non-blocking
  // connect(2).
  connected = true;

  r = sock->attach(reinterpret_cast<hadoop::rpc::ev::EvEventLoop*>(loop));
  if (r != 0) return -1;

  return 0;
}

int EvTransport::sendPendingMessages()
{
  int r;
  while (!pendingMessages.empty()) {
    const pair<void*, size_t>& p = pendingMessages.front();

    r = sock->send(p.first, p.second);
    if (r != 0)
      return -1;

    pendingMessages.pop_front();
  }
  return 0;
}

void EvTransport::onRead(void* buf)
{
}

void EvTransport::onMessage(void* msg)
{
}

void EvTransport::close()
{
}

} // namespace ev
} // namespace rpc
} // namespace hadoop

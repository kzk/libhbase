#include "rpc/ev/ev_transport.hpp"
#include "rpc/ev/ev_socket.hpp"

#include <ev.h>
#include <cassert>
#include <vector>

using namespace std;

namespace hadoop {
namespace rpc {
namespace ev {
EvTransport::EvTransport(const string& addr)
  : Transport(addr)
{
}

EvTransport::~EvTransport()
{
}

int EvTransport::open()
{
  int r;
  EvSocket *s = new EvSocket();
  if (s == NULL) return -1;

  r = s->open(addr);
  if (r != 0) return -1;

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

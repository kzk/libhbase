#include "rpc/client.hpp"
#include "rpc/event_loop.hpp"
#include "rpc/transport.hpp"

using namespace std;

namespace hadoop {
namespace rpc {

Client::Client(const std::string& addr, EventLoop* loop)
  : addr(addr), loop(loop), tran(loop->openTransport(addr))
{
}

Client::~Client()
{
}

int Client::callAsync(void* msg, size_t msglen)
{
  int r;
  if (!tran->isOpened()) {
    r = tran->open();
    if (r != 0) return -1;
  }
  r = tran->sendMessage(msg, msglen);
  return r;
}

void Client::close()
{
}

} // namespace rpc
} // namespace hadoop

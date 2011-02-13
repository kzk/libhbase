#include "event_loop.hpp"
#include "rpc/libev/ev_event_loop.hpp"

using namespace std;

namespace hadoop {
namespace rpc {

EventLoop* CreateEventLoop(const string& type)
{
  if (type == "libev")
    return new hadoop::rpc::ev::EvEventLoop();
  return NULL;
}

} // namespace rpc
} // namespace hadoop

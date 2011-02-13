#include "rpc/libev/ev_event_loop.hpp"

namespace hadoop {
namespace rpc {
namespace ev {

EvEventLoop::EvEventLoop()
  : evloop(ev_loop_new(0))
{
}

EvEventLoop::~EvEventLoop()
{
  ev_loop_destroy(evloop);
}

void EvEventLoop::run()
{
  int flag = 0;
  ev_run(evloop, flag);
}

void EvEventLoop::runOnce()
{
  int flag = EVRUN_ONCE;
  ev_run(evloop, flag);
}

} // namespace ev
} // namespace rpc
} // namespace hadoop

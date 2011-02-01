#include "rpc/ev/ev_event_loop.hpp"

namespace hadoop {
namespace rpc {
namespace ev {

EvEventLoop::EvEventLoop()
  : loop(ev_loop_new(0))
{
}

EvEventLoop::~EvEventLoop()
{
  ev_loop_destroy(loop);
}

void EvEventLoop::run()
{
  int flag = 0;
  ev_run(loop, flag);
}

void EvEventLoop::runOnce()
{
  int flag = EVRUN_ONCE;
  ev_run(loop, flag);
}

} // namespace ev
} // namespace rpc
} // namespace hadoop

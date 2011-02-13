#include <gtest/gtest.h>
#include "rpc/event_loop.hpp"
#include "rpc/transport.hpp"

#include <vector>
#include <string>
#include <iostream>

using namespace std;
using namespace hadoop::rpc;

TEST(EventLoopTest, open_and_close) {
  int r;
  EventLoop* loop = CreateEventLoop("libev");
  ASSERT_TRUE(loop != NULL);
  Transport* tran = loop->openTransport("localhost:19850");
  ASSERT_TRUE(tran != NULL);
  r = tran->open();
  EXPECT_EQ(0, r);
  tran->close();
}

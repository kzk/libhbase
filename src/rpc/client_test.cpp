#include <gtest/gtest.h>
#include "rpc/client.hpp"

#include <vector>
#include <string>
#include <iostream>

using namespace std;
using namespace hadoop::rpc;

TEST(ClentTest, open_and_close) {
  EventLoop* loop = CreateEventLoop("libev");
  ASSERT_TRUE(loop != NULL);

  Client* cln = new Client("localhost:22", loop);
  ASSERT_TRUE(cln != NULL);

  int r;
  string buf = "aiueo";
  r = cln->callAsync((void*)buf.c_str(), buf.size()); // FIXME for void*
  ASSERT_EQ(0, r);

  delete cln;
  delete loop;
}

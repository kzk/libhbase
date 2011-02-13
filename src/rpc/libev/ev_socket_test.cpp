#include <gtest/gtest.h>
#include "ev_socket.hpp"

#include <vector>
#include <string>
#include <iostream>

using namespace std;
using namespace hadoop::rpc::ev;

TEST(EvSocketTest, open_and_close) {
  EvSocket* sock = new EvSocket();
  ASSERT_TRUE(sock != NULL);
  ASSERT_EQ(0, sock->open("localhost:22"));
  sock->close();
  delete sock;
}

TEST(EvSocketTest, cannot_connect) {
  EvSocket* sock = new EvSocket();
  ASSERT_TRUE(sock != NULL);
  ASSERT_EQ(-1, sock->open("not-found-domain:22"));
  sock->close();
  delete sock;
}

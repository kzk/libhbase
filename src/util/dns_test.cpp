#include <gtest/gtest.h>
#include "dns.hpp"

#include <vector>
#include <string>
#include <iostream>

using namespace std;
using namespace hadoop::util;

TEST(DNSTest, google) {
  int r;
  vector<IPv4Addr> v;
  r = DNSResolver::resolve("localhost", "80", v);
  ASSERT_EQ(0, r);
  EXPECT_TRUE(v.size() > 0);
}

TEST(DNSTest, not_found_test) {
  int r;
  vector<IPv4Addr> v;
  r = DNSResolver::resolve("not-found-domain", "80", v);
  ASSERT_EQ(-1, r);
}

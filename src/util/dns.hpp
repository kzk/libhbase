#ifndef _HADOOP_UTIL_DNS_HPP_
#define _HADOOP_UTIL_DNS_HPP_

#include <string>
#include <vector>

namespace hadoop {
namespace util {

class IPv4Addr {
public:
  IPv4Addr(const std::string& s);
  std::string toString() const;

private:
  unsigned char ip[4];
};

class DNSResolver {
public:
  static int resolve(const std::string& host,
                     const std::string& port,
                     std::vector<IPv4Addr>& ret);
};

} // namespace util
} // namespace hadoop

#endif /* Not def: _HADOOP_UTIL_DNS_HPP_ */

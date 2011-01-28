#ifndef _ZOOKEEPER_UTIL_HPP_
#define _ZOOKEEPER_UTIL_HPP_

#include <stdint.h>
#include <vector>
#include <string>
#include <cassert>

namespace hadoop {
namespace zookeeper {
class ZooKeeperWatcher;

class ZooKeeperUtil {
public:
  static int createAndFailSilent(ZooKeeperWatcher* w, const std::string& path);
  static int watchAndCheckExists(ZooKeeperWatcher* w, const std::string& path);
  static int getDataAndWatch(ZooKeeperWatcher* w, const std::string& path,
                             std::vector<char>& data);
};

} // namespace zookeeper
} // namespace hadoop

#endif /* Not def: _ZOOKEEPER_UTIL_HPP_ */

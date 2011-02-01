#ifndef _ROOT_REGION_TRACKER_HPP_
#define _ROOT_REGION_TRACKER_HPP_

#include "zookeeper/zookeeper_node_tracker.hpp"
#include <string>

namespace hadoop {
namespace zookeeper {
class ZooKeeperWatcher;
} // namespace zookeeper

namespace hbase {

class RootRegionTracker : public hadoop::zookeeper::ZooKeeperNodeTracker
{
public:
  RootRegionTracker(hadoop::zookeeper::ZooKeeperWatcher* w)
    : ZooKeeperNodeTracker(w, "/hbase/root-region-server") {}
  virtual ~RootRegionTracker() {}

  bool isRootRegionAvailable() const { return !data.empty(); }
  std::string getRootRegionLocation() {
    return isRootRegionAvailable()
      ? std::string((const char*)&data[0])
      : std::string();
  }
};

} // namespace hbase
} // namespace hadoop

#endif /* Not def: _ROOT_REGION_TRACKER_HPP_ */

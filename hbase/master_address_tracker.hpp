#ifndef _MASTER_ADDRESS_TRACKER_HPP_
#define _MASTER_ADDRESS_TRACKER_HPP_

#include "zookeeper/zookeeper_node_tracker.hpp"

namespace hadoop {
namespace zookeeper {
class ZooKeeperWatcher;
} // namespace zookeeper

namespace hbase {

class MasterAddressTracker : public hadoop::zookeeper::ZooKeeperNodeTracker
{
public:
  MasterAddressTracker(hadoop::zookeeper::ZooKeeperWatcher* w)
    : ZooKeeperNodeTracker(w, "/hbase/master") {}
  virtual ~MasterAddressTracker() {}
};

} // namespace hbase
} // namespace hadoop

#endif /* Not def: _MASTER_ADDRESS_TRACKER_HPP_ */

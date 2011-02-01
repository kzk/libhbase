#ifndef _HBASE_CONNECTION_HPP_
#define _HBASE_CONNECTION_HPP_

#include "master_address_tracker.hpp"
#include "root_region_tracker.hpp"

namespace hadoop {
namespace zookeeper {
class ZooKeeperWatcher;
}
namespace hbase {

class Connection {
public:
  Connection();
  ~Connection();

  int initialize();

protected:
  int setupZooKeeperTrackers();

protected:
  hadoop::zookeeper::ZooKeeperWatcher* zooKeeper;
  MasterAddressTracker masterAddressTracker;
  RootRegionTracker rootRegionTracker;
};

} // namespace hbase
} // namespace hadoop

#endif /* Not def: _HBASE_CONNECTION_HPP_ */

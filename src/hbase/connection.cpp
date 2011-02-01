#include "connection.hpp"
#include "zookeeper/zookeeper_watcher.hpp"

using namespace std;
using hadoop::zookeeper::ZooKeeperWatcher;

namespace hadoop {
namespace hbase {

Connection::Connection()
  : zooKeeper(new ZooKeeperWatcher),
    masterAddressTracker(zooKeeper),
    rootRegionTracker(zooKeeper)
{
}

Connection::~Connection()
{
  if (zooKeeper) {
    delete zooKeeper;
    zooKeeper = NULL;
  }
}

int Connection::initialize()
{
  int r;
  r = zooKeeper->initialize();
  if (r != 0) return -1;

  r = setupZooKeeperTrackers();
  if (r != 0) return -1;
  return 0;
}

int Connection::setupZooKeeperTrackers()
{
  int r;
  r = masterAddressTracker.start();
  if (r != 0) return r;

  r = rootRegionTracker.start();
  if (r != 0) return r;

  sleep(1);

  cout << "masterAddr:" << masterAddressTracker.getMasterAddress() << endl;
  cout << "rootRegion:" << rootRegionTracker.getRootRegionLocation() << endl;

  return 0;
}

} // namespace hbase
} // namespace hadoop

#include "zookeeper_node_tracker.hpp"
#include "zookeeper_watcher.hpp"
#include "util/condition.hpp"

#include <zookeeper.h>

#include <vector>
#include <string>

using namespace std;

namespace hadoop {
namespace zookeeper {

ZooKeeperNodeTracker::ZooKeeperNodeTracker(ZooKeeperWatcher* w,
                                           const string& path)
  : ZooKeeperEvent(w), path(path), w(w)
{
}

ZooKeeperNodeTracker::~ZooKeeperNodeTracker()
{
}

int ZooKeeperNodeTracker::start()
{
  int r;

  hadoop::util::ScopedLock lk(data_lk);
  data.clear();

  r = w->registerEvent(this);
  if (r != 0) return -1;

  r = ZooKeeperUtil::watchAndCheckExists(w, path);
  if (r != 0) return 0;

  r = ZooKeeperUtil::getDataAndWatch(w, path, data);
  return (r == 0 && !data.empty()) ? 0 : -1;
}

void ZooKeeperNodeTracker::onNodeCreated(const string& p)
{
  int r;
  if (path != p) return;
  {
    hadoop::util::ScopedLock lk(data_lk);
    r = ZooKeeperUtil::getDataAndWatch(w, p, data);
  }
  if (r != 0)
    onNodeDeleted(p);
}

void ZooKeeperNodeTracker::onNodeDeleted(const string& p)
{
  int r;
  if (path != p) return;
  r = ZooKeeperUtil::watchAndCheckExists(w, p);
  if (r == 0) {
    onNodeCreated(p);
  } else {
    hadoop::util::ScopedLock lk(data_lk);
    data.clear();
  }
}

void ZooKeeperNodeTracker::onDataChanged(const string& p)
{
  if (path != p) return;
  onNodeCreated(p);
}

} // namespace zookeeper
} // namespace hadoop

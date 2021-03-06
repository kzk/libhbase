#ifndef _ZOOKEEPER_NODE_TRACKER_HPP_
#define _ZOOKEEPER_NODE_TRACKER_HPP_

#include "zookeeper_event.hpp"
#include "zookeeper_util.hpp"
#include "util/lock.hpp"

namespace hadoop {
namespace zookeeper {
class ZooKeeperWatcher;

class ZooKeeperNodeTracker : public ZooKeeperEvent
{
public:
  ZooKeeperNodeTracker(ZooKeeperWatcher* w, const std::string& node);
  virtual ~ZooKeeperNodeTracker();

  int start();
  void getPath(std::string& p) { p = path; }
  void getData(std::vector<char>& d) {
    hadoop::util::ScopedLock lk(data_lk);
    d = data;
  };

public:
  // callbacks
  virtual void onNodeCreated(const std::string& path);
  virtual void onNodeDeleted(const std::string& path);
  virtual void onDataChanged(const std::string& path);

protected:
  hadoop::util::Lock data_lk;

  std::string path;
  std::vector<char> data;
  ZooKeeperWatcher *w;
};

} // namespace zookeeper
} // namespace hadoop

#endif /* Not def: _ZOOKEEPER_NODE_TRACKER_HPP_ */

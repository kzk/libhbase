#include "zookeeper_watcher.hpp"
#include "zookeeper_event.hpp"
#include "zookeeper_util.hpp"

#include <iostream>
#include <unistd.h>
#include <string>

using namespace std;

namespace hadoop {
namespace zookeeper {
namespace {
void watcher_callback(zhandle_t *zk, int type, int state,
                      const char *path, void *ctx)
{
  ZooKeeperWatcher *watcher = (ZooKeeperWatcher*)ctx;
  if (watcher == NULL) return;
  watcher->callback(type, state, string(path));
}
} // namespace

ZooKeeperWatcher::ZooKeeperWatcher()
  : zk(NULL)
{
}

ZooKeeperWatcher::~ZooKeeperWatcher()
{
  if (zk != NULL) {
    zookeeper_close(zk);
    zk = NULL;
  }

  events.erase(unique(events.begin(), events.end()), events.end());
  for (unsigned int i = 0; i < events.size(); i++) {
    cerr << "p=" << events[i] << endl;
    delete events[i];
  }
  events.clear();
}

int ZooKeeperWatcher::initialize()
{
  zk = zookeeper_init("127.0.0.1:2181", watcher_callback, 10000, 0, this, 0);
  if (zk == NULL)
    return -1;

  if (ensureNodeExistence("/hbase") != 0
      || ensureNodeExistence("/hbase/unassigned") != 0
      || ensureNodeExistence("/hbase/rs") != 0
      || ensureNodeExistence("/hbase/table") != 0)
    return -1;

  return 0;
}

int ZooKeeperWatcher::registerEvent(ZooKeeperEvent* e)
{
  events.push_back(e);
  return 0;
}

int ZooKeeperWatcher::callback(int type, int state, const string& path)
{
  cerr << "ZooKeeperWatcher::callback: type=" << type << ", state="
       << state << endl;
  if (type == ZOO_CREATED_EVENT) {
    for (unsigned int i = 0; i < events.size(); i++)
      events[i]->onNodeCreated(path);
  } else if (type == ZOO_DELETED_EVENT) {
    for (unsigned int i = 0; i < events.size(); i++)
      events[i]->onNodeDeleted(path);
  } else if (type == ZOO_CHANGED_EVENT) {
    for (unsigned int i = 0; i < events.size(); i++)
      events[i]->onDataChanged(path);
  } else if (type == ZOO_CHILD_EVENT) {
    for (unsigned int i = 0; i < events.size(); i++)
      events[i]->onChildrenChanged(path);
  }
  return 0;
}

int ZooKeeperWatcher::ensureNodeExistence(const string& path)
{
  return ZooKeeperUtil::createAndFailSilent(this, path);
}

} // namespace zookeeper
} // namespace hadoop

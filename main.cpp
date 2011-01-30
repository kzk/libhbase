#include "hbase/connection.hpp"
#include "zookeeper/zookeeper_watcher.hpp"
#include "hbase/master_address_tracker.hpp"
#include <iostream>

using namespace std;

int main()
{
  /*
  int r;
  hadoop::zookeeper::ZooKeeperWatcher w;
  r = w.initialize();
  cerr << r << endl;

  hadoop::hbase::MasterAddressTracker* masterAddressTracker = new hadoop::hbase::MasterAddressTracker(&w);
  r = masterAddressTracker->start();
  cerr << r << endl;
  
  sleep(1);

  vector<char> data;
  masterAddressTracker->getData(data);
  cerr << "data: " << data.size() << endl;

  string s((const char*)&data[0]);
  cerr << "addr: " << s << endl;
  */

  hadoop::hbase::Connection c;
  cerr << c.initialize() << endl;

  return 0;
}

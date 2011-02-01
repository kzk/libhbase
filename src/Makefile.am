lib_LTLIBRARIES = libhbase.la

libhbase_la_SOURCES = \
  ./hbase/connection.cpp \
  ./hbase/connection.hpp \
  ./hbase/connection_manager.hpp \
  ./hbase/master_address_tracker.hpp \
  ./hbase/root_region_tracker.hpp \
  ./zookeeper/zookeeper_event.hpp \
  ./zookeeper/zookeeper_node_tracker.cpp \
  ./zookeeper/zookeeper_node_tracker.hpp \
  ./zookeeper/zookeeper_util.cpp \
  ./zookeeper/zookeeper_util.hpp \
  ./zookeeper/zookeeper_watcher.cpp \
  ./zookeeper/zookeeper_watcher.hpp \
  ./util/condition.hpp \
  ./util/lock.hpp

libhbase_la_CXXFLAGS = \
  -I$(top_srcdir)/src/ \
  -I/usr/local/include/c-client-src

# -version-info CURRENT:REVISION:AGE
libhbase_la_LDFLAGS = -version-info 1:0:0

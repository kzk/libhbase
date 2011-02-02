lib_LTLIBRARIES = libhbase.la

libhbase_la_SOURCES = \
  ./rpc/event_loop.hpp \
  ./rpc/transport.hpp \
  ./rpc/ev/ev_event_loop.hpp \
  ./rpc/ev/ev_event_loop.cpp \
  ./rpc/ev/ev_transport.hpp \
  ./rpc/ev/ev_transport.cpp \
  ./rpc/ev/ev_socket.hpp \
  ./rpc/ev/ev_socket.cpp \
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
  ./util/lock.hpp \
  ./util/dns.hpp \
  ./util/dns.cpp \
  ./util/syscall.hpp

libhbase_la_CXXFLAGS = \
  -I$(top_srcdir)/src/ \
  -I/usr/local/include/c-client-src

# -version-info CURRENT:REVISION:AGE
libhbase_la_LDFLAGS = -version-info 1:0:0

libhbase_la_LIBADD = -lzookeeper_mt

# unittests
check_PROGRAMS = \
  rpc_ev_ev_socket_test \
  dns_test

rpc_ev_ev_socket_test_SOURCES = rpc/ev/ev_socket_test.cpp
rpc_ev_ev_socket_test_LDADD = libhbase.la -lgtest_main -lgtest

dns_test_SOURCES = util/dns_test.cpp
dns_test_LDADD = libhbase.la -lgtest_main -lgtest

TESTS = $(check_PROGRAMS)

#ifndef _HADOOP_RPC_TRANSPORT_HPP_
#define _HADOOP_RPC_TRANSPORT_HPP_

#include "util/lock.hpp"
#include <string>

namespace hadoop {
namespace rpc {
class EventLoop;

class Transport {
public:
  Transport(EventLoop* loop, const std::string& addr)
    : loop(loop), addr(addr), opened(false) {}
  virtual ~Transport() {}

  virtual int open() {
    hadoop::util::ScopedLock lk(tran_lk);
    opened = true;
    return 0;
  };
  virtual bool isOpened() {
    hadoop::util::ScopedLock lk(tran_lk);
    return opened;
  }
  virtual int sendMessage(void* msg, size_t msglen) = 0;
  virtual void onRead(void* buf) = 0;
  virtual void onMessage(void* msg) = 0;
  virtual void close() = 0;

protected:
  hadoop::util::Lock tran_lk;
  hadoop::rpc::EventLoop* loop;
  std::string addr;
  bool opened;
};

} // namespace rpc
} // namespace hadoop

#endif /* Not def: _HADOOP_RPC_TRANSPORT_HPP_ */

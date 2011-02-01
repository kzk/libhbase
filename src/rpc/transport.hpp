#ifndef _HADOOP_RPC_TRANSPORT_HPP_
#define _HADOOP_RPC_TRANSPORT_HPP_

#include <string>

namespace hadoop {
namespace rpc {

class Transport {
public:
  Transport(const std::string& addr) : addr(addr) {}
  virtual ~Transport() {}

  virtual int open() = 0;
  virtual void onRead(void* buf) = 0;
  virtual void onMessage(void* msg) = 0;
  virtual void close() = 0;

protected:
  std::string addr;
};

} // namespace rpc
} // namespace hadoop

#endif /* Not def: _HADOOP_RPC_TRANSPORT_HPP_ */
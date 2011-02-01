#include "util/dns.hpp"

#include <sys/socket.h>
#include <netdb.h>
#include <sstream>

using namespace std;

namespace hadoop {
namespace util {

IPv4Addr::IPv4Addr(const string& s)
{
  int a = -1, b = -1, c = -1, d = -1;
  char x='\0', y='\0', z='\0';
  istringstream iss(s);
  if (!((iss>>a>>x>>b>>y>>c>>z>>d) &&
        a>=0 && a<=255&&
        b>=0 && b<=255&&
        c>=0 && c<=255&&
        d>=0 && d<=255&&
        x=='.'&&
        y=='.'&&
        z=='.')) {
    return;
  }
  ip[0] = (unsigned char)a;
  ip[1] = (unsigned char)b;
  ip[2] = (unsigned char)c;
  ip[3] = (unsigned char)d;
}

string IPv4Addr::toString() const
{
  ostringstream oss;
  oss<<(int)ip[0]<<'.'<<(int)ip[1]<<'.'<<(int)ip[2]<<'.'<<(int)ip[3];
  return oss.str();
};

int DNSResolver::resolve(const string& host, const string& port,
                         vector<IPv4Addr>& ret)
{
  int r;
  addrinfo hints = {};
  hints.ai_family = PF_INET;
  hints.ai_socktype = SOCK_STREAM;
  hints.ai_protocol = 0;

  addrinfo *res=NULL;
  if (getaddrinfo(host.c_str(), port.c_str(), &hints, &res)!=0)
    return -1;

  for (addrinfo *p = res; p != NULL; p = p->ai_next) {
    char ips[32]; // xxx.xxx.xxx.xxx
    r = getnameinfo(p->ai_addr, p->ai_addrlen, ips, 32, NULL, 0, NI_NUMERICHOST);
    if (r != 0) continue;

    IPv4Addr ip(ips);
    ret.push_back(ip);
  }

  freeaddrinfo(res);
  return 0;
}

} // namespace util
} // namespace hadoop

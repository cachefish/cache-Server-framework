#include"InetAddress.h"
#include<string.h>
#include<stdio.h>
#include<stdlib.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>

namespace cf
{
static_assert(sizeof(InetAddress)==sizeof(struct sockaddr_in),"InetAddress Error");

InetAddress::InetAddress(uint16_t port)
{
    ::memset(&addr_,0,sizeof(addr_));
    addr_.sin_family = AF_INET;
    addr_.sin_port = htons(port);
    addr_.sin_addr.s_addr = INADDR_ANY;
}
InetAddress::InetAddress(const std::string&ip,uint16_t port)
{
    ::memset(&addr_,0,sizeof(addr_));
    addr_.sin_family = AF_INET;
    addr_.sin_port = htons(port);
    if(inet_aton(ip.c_str(),&addr_.sin_addr)==0)
    {
        fprintf(stderr,"ip invalid\n");
        exit(EXIT_FAILURE);
    }
}
InetAddress::InetAddress(const struct sockaddr_in &addr):addr_(addr)
{

}
std::string InetAddress::toip()const
{
    return inet_ntoa(addr_.sin_addr);
}
uint16_t InetAddress::toPort()const
{
    return ntohs(addr_.sin_port);
}
} // namespace cf


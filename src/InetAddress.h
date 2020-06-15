#ifndef _INADDRESS_H
#define _INADDRESS_H

#include<string>
#include<netinet/in.h>

namespace cf
{

typedef struct sockaddr SA;
typedef struct sockaddr_in SAI;

class InetAddress
{
    public:
        InetAddress(uint16_t port);
        InetAddress(const std::string&ip,uint16_t port);
        InetAddress(const struct sockaddr_in &addr);

        //set addr
        void setSockAddrInet(const struct sockaddr_in &addr)
        {
            addr_=addr;
        }
        //get addr
        const struct sockaddr_in*getSockAddrInet()const
        {
            return &addr_;
        }

        std::string toip()const;
        uint16_t toPort()const;
    private:
        struct sockaddr_in addr_;
};

} // namespace cf





#endif
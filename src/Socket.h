#ifndef _SOCKET_H
#define _SOCKET_H

#include"NonCopyable.h"
#include"InetAddress.h"

namespace cf
{
    class Socket:NonCopyable
    {
        public:
            explicit Socket(int sockfd);
            ~Socket();
        
            int fd()const{return sockfd_;}
            void bindAddress(const InetAddress &addr);
            void listen();
            void accept();

            void shutdownWrite();

            void setTcpNoDelay(bool on);
            void setReuseAddr(bool on);
            void setReusePort(bool on);
            void setKeepAlive(bool on);

            static InetAddress getLocalAddress(int sockfd);
            static InetAddress getPeerAddress(int sockfd);
        private:
            const int sockfd_;
    };


} // namespace cf



#endif
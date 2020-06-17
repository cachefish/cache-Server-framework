#ifndef TCP_SERVER_H
#define TCP_SERVER_H
#include"NonCopyable.h"
#include"EpollPoller.h"
#include"SocketIO.h"

namespace cf
{
    class TcpServer:NonCopyable
    {
        public:
            using TcpServerCallback = EpollPoller::EpollCallback;
        
        explicit TcpServer(const InetAddress&addr);

        void start()
        {
            poller_.loop();
        }
        void setConnectCallback(TcpServerCallback cb)
        {
            poller_.setConnectCallback(std::move(cb));
        }

        void setMessageCallback(TcpServerCallback cb)
        {
            poller_.setMessageCallback(std::move(cb));
        }
        void setCloseCallback(TcpServerCallback cb)
        {
            poller_.setCloseCallback(std::move(cb));
        }
        private:
            Socket sockfd_;
            EpollPoller poller_;
    };

}

#endif
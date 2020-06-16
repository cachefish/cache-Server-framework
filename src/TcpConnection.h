#ifndef TCP_CONNECTION_H
#define TCP_CONNECTION_H

#include"NonCopyable.h"
#include<memory>
#include<functional>
#include"Socket.h"
#include"SocketIO.h"

namespace cf
{
    class TcpConnection;
    using TcpConnectionPtr = std::shared_ptr<TcpConnection>;

    class TcpConnection:NonCopyable,public std::enable_shared_from_this<TcpConnection>
    {  // 回调函数的参数为：管理TcpConnection对象的智能指针shared_ptr的常量引用，
    // 之所以需要这个参数，是因为外部传入的回调函数需要用到TcpConnection对象对外提供的函数接口
        public:
            using TcpConnectionCallback = std::function<void(const TcpConnectionPtr&)>;
            explicit TcpConnection(int sockfd);
            ~TcpConnection();
            //传入回调函数
            void setConnectionCallback(TcpConnectionCallback cb){
                onConnectionCallback_ = cb;
            }
            void setMessageCallback(TcpConnectionCallback cb)
            {
                onMessageCallback_ = cb;
            }
            void setCloseCallback(TcpConnectionCallback cb)
            {
                onCloseCallback_ = cb;
            }
            
           //执行回调函数
            void handleConnectionCallback();
            void handleMessageCallback();
            void handleCloseCallback();

            void shutdown(){
                sockfd_.shutdownWrite();
                isShutdownWrite_=true;
            }

            ssize_t readn(char*buf,size_t count);
            ssize_t writen(const char *buf,size_t count);
            ssize_t readLine(char*usrbuf,size_t maxlen);
            std::string receive();
            void send(const std::string&s);

            const InetAddress&getLocalAddr()const
            {
                return localAddr_;
            }                
            const InetAddress&getPeerAddr()const
            {
                return peerAddr_;
            }

            std::string toString()const;

            private:
                Socket sockfd_;
                SocketIO sockIO_;
                const InetAddress localAddr_;
                const InetAddress peerAddr_;
                bool isShutdownWrite_;

                TcpConnectionCallback onConnectionCallback_;
                TcpConnectionCallback onMessageCallback_;
                TcpConnectionCallback onCloseCallback_;


    };

}

#endif
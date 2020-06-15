#ifndef _SOCKETIO_H_
#define _SOCKETIO_H_
#include"NonCopyable.h"
#include<unistd.h>

namespace cf
{
    class SocketIO
    {
        public:
            explicit SocketIO(int fd);

            ssize_t readn(char *usrbuf,size_t count);
            ssize_t readLine(char*usrbuf,size_t maxlen);
            ssize_t writen(int fd,const void *buf,size_t count);

        private:
            ssize_t read(char *usrbuf,size_t n);
            size_t recv_peek(char * buf, size_t count);
            static const int kBufferSize = 65536;
        private:
            int fd_;                 //fd
            int cnt_;               //缓冲区可用的字节数
            char*ptr_;           //指向缓冲区可用的第一个字节
            char buffer_[kBufferSize];          //缓冲区
    };



}
#endif
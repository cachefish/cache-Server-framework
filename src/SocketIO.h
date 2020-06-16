#ifndef _SOCKETIO_H_
#define _SOCKETIO_H_
#include"NonCopyable.h"
#include <sys/types.h>

namespace cf
{
class SocketIO : NonCopyable
{
public: 
    explicit SocketIO(int sockfd)
    : sockfd_(sockfd)
    {
    }

    ssize_t readn(char *buf, size_t count);
    ssize_t writen(const char *buf, size_t count);
    ssize_t readline(char *usrbuf, size_t maxlen);
private:
    ssize_t recv_peek(char *buf, size_t len);

    const int sockfd_;
};

}
#endif //SOCKETIO_H_
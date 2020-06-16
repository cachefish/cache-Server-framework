#include"Timer.h"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdint.h>
#include<sys/timerfd.h>
#include<time.h>
#include<unistd.h>
#include<poll.h>
#include<errno.h>

#define ERR_EXIT(m)\
    do{ \
        perror(m);\
        exit(EXIT_FAILURE);\    
    }while(0)

namespace  
{

    const long  KNsecondsOfPerSecond = 1000*1000*1000;

    int createTimerfd()
    {
        int timerfd = ::timerfd_create(CLOCK_REALTIME,0);
        if(timerfd==-1)
        {
            ERR_EXIT("timerfd_create error");
        }
        return timerfd;
    }

    void setTimerfd(int timerfd,double value,double interval)
    {
        struct itimerspec val;
        memset(&val,0,sizeof(val));
        val.it_value.tv_sec = (time_t)value;
        val.it_value.tv_nsec = (value-(time_t )value)*KNsecondsOfPerSecond;
        val.it_interval.tv_sec = (time_t)interval;
        val.it_interval.tv_nsec = (interval-(time_t)interval)*KNsecondsOfPerSecond;

        if(::timerfd_settime(timerfd,0,&val,NULL)==-1)
        {
            ERR_EXIT("timerfd_settime");
        }        
    }

    void stopTimerfd(int timerfd)
    {
         // 将起始时间和间隔时间都置为0，定时器就停止了，timerfd就不活动了，poll也就监测不到了
        setTimerfd(timerfd, 0, 0); 
    }

    void readTimerfd(int timerfd)
    {
        uint64_t howmany;
        //必须将timerfd中的内容取走，不然poll会水平触发
        if(::read(timerfd,&howmany,sizeof(howmany))!=sizeof(howmany))
        {
            ERR_EXIT("read timerfd error");
        }
    }
}

namespace cf
{

Timer::Timer(double val,double interval,TimerCallback cb)
:timerfd_(createTimerfd())
,val_(val)
,interval_(interval)
,callback_(std::move(cb))
,isStarted_(false)
{

}

Timer::~Timer()
{
    if(isStarted_)
    {
        stop();
        ::close(timerfd_);
    }
}

void Timer::start()
{
    setTimerfd(timerfd_,val_,interval_);
    isStarted_ = true;
    struct pollfd pfd;
    pfd.fd = timerfd_;
    pfd.events = POLLIN;

    uint64_t val;
    int ret;
    while(isStarted_)
    {
        ret = ::poll(&pfd,1,5000);
        if(ret == -1)
        {
            if(errno == EINTR)
            [
                continue;
            }
            ERR_EXIT(poll);
        }
        else if(ret==0)
        {
            printf("timeout\n");     
        }
        else {
            if(pfd.revents == POLLIN)
            {
                readTimerfd(timerfd_);
                callback_();
            }
        }
    }
}
void Timer::stop()
{
    isStarted_=false;
    stopTimerfd(timerfd_);
}


}



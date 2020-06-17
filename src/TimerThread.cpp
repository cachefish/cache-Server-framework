#include"TimerThread.h"
namespace cf
{
    TimerThread::TimerThread(double value,double interval,Callback cb)
    :timer_(value,interval,std::move(cb))
    ,thread_(std::bind(&Timer::start,&timer_))
    {
    
    }

    void TimerThread::start()
    {
        thread_.start();
    }

    void TimerThread::stop()
    {
        timer_.stop();
        thread_.join();
    }
}
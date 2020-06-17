#ifndef TIMER_THREAD_H
#define TIMER_THREAD_H

#include"NonCopyable.h"
#include"Timer.h"
#include"Thread.h"
#include<functional>

namespace cf
{
    class TimerThread
    {
        public: 
            using Callback = std::function<void()>;
            TimerThread(double value,double interval,Callback cb);

            void start();
            void stop();
        private:
            Timer timer_;
            Thread thread_;
    };

}


#endif
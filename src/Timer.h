#ifndef TIMER_H
#define TIMER_H
#include"NonCopyable.h"
#include<functional>

namespace cf
{
    class Timer:NonCopyable
    {
        public:
            using TimerCallback = std::function<void()>;

            Timer(double val,double interval,TimerCallback cb);
            ~Timer();

            void start();
            void stop();

        private:
            int timerfd_;
            double val_;
            double interval_;
            TimerCallback callback_;
            bool isStarted_;
    };


}









#endif
#ifndef CONDITION_H
#define CONDITION_H
#include"NonCopyable.h"
#include<pthread.h>

namespace cf
{
    class MutexLock;

    class Condition
    {
        public:
            Condition(MutexLock&mutex);
            ~Condition();

            void wait();
            void notify();
            void notifyAll();

        private:
            MutexLock &mutex_;
            pthread_cond_t cond_;
    };
    

}
#endif
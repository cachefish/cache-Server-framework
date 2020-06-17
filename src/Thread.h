#ifndef _THREAD_H
#define _THREAD_H

#include"NonCopyable.h"
#include<pthread.h>
#include<functional>

namespace cf
{
    class Thread:NonCopyable
    {
        public:
            using ThreadCallback = std::function<void()>;
            
            explicit Thread(ThreadCallback&&cb);
            virtual ~Thread();

            void start();
            void join();

            pthread_t getThreadId()const;
        private:
            static void *runInTHread(void*arg);

        private:
            pthread_t threadId_;
            bool isRunning_;
            ThreadCallback callback_;
    };

    inline pthread_t Thread::getThreadId()const{
        return threadId_;
    }




}



#endif
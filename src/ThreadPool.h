#ifndef _THREADPOOL_H
#define _THREADPOOL_H
#include"NonCopyable.h"
#include"MutexLock.h"
#include"Condition.h"
#include"Thread.h"
#include<queue>
#include<vector>
#include<functional>
#include<memory>

namespace cf
{
    class ThreadPool:NonCopyable
    {
        public:
            using Task  = std::function<void()>;

            ThreadPool(size_t queueSize,size_t threadNum);
            ~ThreadPool();

            void start();
            void stop();

            void addTask(Task task);
            Task getTask();

            bool isStarted()const;

            void runInThread();

        private:
        mutable MutexLock mutex_;
        Condition empty_;   //等待空间
        Condition full_;        //等待 任务

        size_t queueSize_;  
        std::queue<Task> queue_;

        const size_t threadsNum;  //线程数
        std::vector<std::unique_ptr<Thread>> threads_;
        bool isStarted_;
    };

    inline bool ThreadPool::isStarted()const
    {
        return isStarted_;
    }


}

#endif
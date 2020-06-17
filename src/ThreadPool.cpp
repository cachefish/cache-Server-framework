#include"ThreadPool.h"
#include<assert.h>


namespace cf
{
ThreadPool::ThreadPool(size_t queueSize,size_t threadNum)
:empty_(mutex_)
,full_(mutex_)
,queueSize_(queueSize)
,threadsNum(threadsNum)
,isStarted_(false)
{

}
ThreadPool::~ThreadPool()
{
    if(isStarted_)
    {
        stop();
    }
}

void ThreadPool::start()
{
    isStarted_=true;
    //每个线程都扮演消费者的角色  初始化线程  在回调函数runInThread中 取任务 执行
    for (size_t i = 0; i !=threadsNum; ++i)
    {
        /* code */
        threads_.push_back(std::unique_ptr<Thread>(new Thread(std::bind(&ThreadPool::runInThread,this))));
    }
    //启动线程池中的线程
    for(size_t ix = 0;ix!=threadsNum;++ix)
    {
        threads_[ix]->start();
    }   

}
void ThreadPool::stop()
{
    if(isStarted_==false)
        return ;   
    {
        MutexLockGuard locl(mutex_);
        isStarted_=false;
        //清空每个任务
        while(!queue_.empty()){
            queue_.pop();
        }      
    }
      // 激活所有线程（通知状态改变），防止线程池中的部分线程卡在getTask的wait上
    // ps: 线程池中的任务就是取任务，执行任务
    // 因此我们传给线程池中各个线程的回调函数runInThread就是取任务，执行任务
    full_.notifyAll();
    // 激活添加任务的线程（我的测试程序添加任务使用的是主线程）
    // 如果不激活的话，那么等到任务队列满后，
    // 由于线程池关闭，线程池中取任务的线程关闭，
    // 添加任务的线程会一直卡在empty_.wait()
    empty_.notifyAll();
    for(size_t ix = 0;ix!=threadsNum;++ix)
    {
        threads_[ix]->join();   //清空线程数组
    }
    threads_.clear();
}

void ThreadPool::addTask(Task task)
{
    if(isStarted_)
        return;
    {
        MutexLockGuard lock(mutex_);
        while(isStarted_&&queue_.size()>=queueSize_)
        {
            empty_.wait();
        }
        if(!isStarted_){
            return;
        }else{
            queue_.push(std::move(task));
        }
    }
}

ThreadPool::Task ThreadPool::getTask()
{
    Task task;
    {
        MutexLockGuard lock(mutex_);
        while(isStarted_&&queue_.empty())
        {
            full_.wait();
        }

        if(isStarted_)
        {
            return Task();
        }else{
            assert(!queue_.empty());
            task = queue_.front();
            queue_.pop();
        }
    }
    empty_.notify();
    return task;
}


void ThreadPool::runInThread()
{
    while(isStarted_)
    {
        Task task(getTask());
        if(task)
        {
            task();
        }
        
    }
}


}
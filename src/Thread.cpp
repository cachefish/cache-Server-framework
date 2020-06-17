#include"Thread.h"
#include"MutexLock.h"
#include<assert.h>

namespace cf
{
 
Thread::Thread(ThreadCallback&& cb)
:threadId_(0)
,isRunning_(false)
,callback_(std::move(cb))
{

}
Thread::~Thread()
{
    if(isRunning_)
    {
        MT_CHECK(!pthread_detach(threadId_));
    }
}

void Thread::start()
{
    isRunning_ = true;
    MT_CHECK(!pthread_create(&threadId_,NULL,runInTHread,this));
}
void Thread::join()
{
    assert(isRunning_);
    MT_CHECK(!pthread_join(threadId_,NULL));
    isRunning_ = false;
}
void *Thread::runInTHread(void*arg)
{
    Thread*pt = static_cast<Thread*> (arg);
    if(pt){
      pt->callback_();
    }
    return NULL;
}


}
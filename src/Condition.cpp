#include"Condition.h"
#include"MutexLock.h"
#include<assert.h>

namespace cf
{
Condition::Condition(MutexLock&mutex)
:mutex_(mutex)
{
    MT_CHECK(!pthread_cond_init(&cond_,NULL));
}
 Condition::~Condition()
 {
     MT_CHECK(!pthread_cond_destroy(&cond_));
 }

void  Condition::wait()
{
    assert(mutex_.isLocking());
    MT_CHECK(!pthread_cond_wait(&cond_,mutex_.getMutexPtr()));

    mutex_.restoreMutexStatus();
}
void  Condition::notify()
{
    MT_CHECK(!pthread_cond_signal(&cond_));
}
void  Condition::notifyAll()
{
    MT_CHECK(!pthread_cond_broadcast(&cond_));
}

}
#include"MutexLock.h"
#include<assert.h>

namespace cf
{
MutexLock::MutexLock():isLocking_(false)
{
    MT_CHECK(!pthread_mutex_init(&mutex_,NULL));
}
MutexLock::~MutexLock()
{
    assert(!isLocking());
    MT_CHECK(!pthread_mutex_destroy(&mutex_));
}

void MutexLock::lock()
{
    MT_CHECK(!pthread_mutex_lock(&mutex_));
    isLocking_ = true;
}
void MutexLock::unlock()
{
    isLocking_ =false;
    MT_CHECK(!pthread_mutex_unlock(&mutex_));
}
MutexLockGuard::MutexLockGuard(MutexLock&mutex)
:mutex_(mutex)
{

}
MutexLockGuard::~MutexLockGuard()
{
    mutex_.unlock();
}
} // namespace cf

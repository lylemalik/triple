#include <pthread.h>
#include <thread/cond.h>
#include <thread/mutex.h>
using namespace std;
using namespace triple;

Cond::Cond()
{
    pthread_cond_init(&cond, NULL);
}

void Cond::wait(Mutex *mutex)
{
    pthread_cond_wait(&cond, mutex->get_mutex());
}

void Cond::singal()
{
    pthread_cond_signal(&cond);
}

void Cond::broadcast()
{
    pthread_cond_broadcast(&cond);
}

Cond::~Cond()
{
    pthread_cond_destroy(&cond);
}

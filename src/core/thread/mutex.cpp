#include <thread/mutex.h>
#include <pthread.h>
using namespace std;
using namespace triple;

Mutex::Mutex()
{
    pthread_mutex_init(&mutex, NULL);
}

void Mutex::lock()
{
    pthread_mutex_lock(&mutex);
}

void Mutex::unlock()
{
    pthread_mutex_unlock(&mutex);
}

pthread_mutex_t *Mutex::get_mutex()
{
    return &mutex;
}

Mutex::~Mutex()
{
    pthread_mutex_destroy(&mutex);
}

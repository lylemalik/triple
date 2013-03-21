#ifndef __MUTEX_H__
#define __MUTEX_H__

#include <pthread.h>
using namespace std;
namespace triple
{
    class Mutex
    {
        private:
            pthread_mutex_t mutex;
        public:
            Mutex() {pthread_mutex_init(&mutex, NULL);}
            ~Mutex() {pthread_mutex_destroy(&mutex);}
            void lock() {pthread_mutex_lock(&mutex);}
            void unlock() {pthread_mutex_unlock(&mutex);}
            pthread_mutex_t *get_mutex() {return &mutex;}
    };
}

#endif

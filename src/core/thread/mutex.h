#ifndef __THREAD_MUTEX_H__
#define __THREAD_MUTEX_H__

#include <pthread.h>
using namespace std;

namespace triple
{
    class Mutex
    {
        private:
            pthread_mutex_t mutex;
        public:
            Mutex();
            void lock();
            void unlock();
            pthread_mutex_t *get_mutex();
            ~Mutex();
    };
}
#endif

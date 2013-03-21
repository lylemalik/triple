#ifndef __COND_H__
#define __COND_H__

#include <pthread.h>
#include <mutex.h>
using namespace std;
namespace triple
{
    class Cond
    {
        private:
            pthread_cond_t cond;
        public:
            Cond() {pthread_cond_init(&cond, NULL);}
            ~Cond() {pthread_cond_destroy(&cond);}
            void wait(Mutex *mutex) {pthread_cond_wait(&cond, mutex->get_mutex());}
            void singal() {pthread_cond_signal(&cond);}
    };
}

#endif

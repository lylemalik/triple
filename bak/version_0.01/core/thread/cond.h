#ifndef __THREAD_COND_H__
#define __THREAD_COND_H__

#include <pthread.h>
#include <thread/mutex.h>
using namespace std;
namespace triple
{
    class Cond
    {
        private:
            pthread_cond_t cond;
        public:
            Cond();
            void wait(Mutex *mutex);
            void singal();
            void broadcast();
            ~Cond();
    };
}
#endif

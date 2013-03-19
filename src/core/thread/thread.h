#ifndef __THREAD_THREAD_H__
#define __THREAD_THREAD_H__

#include <pthread.h>
using namespace std;
namespace triple
{
    class Thread
    {
        private:
            pthread_t pid;
        public:
            void start();
            void join();
            pthread_t get_pid();
            virtual void run(){};
            static void *proxy(void *args);
    };
}

#endif

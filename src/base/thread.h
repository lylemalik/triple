#ifndef __THREAD_H__
#define __THREAD_H__

#include <pthread.h>
using namespace std;
namespace triple
{
    class Thread;
    //简单的封装线程，这是一个基类，任何具体线程从这个基类继承，
    //并且实现它的run方法即可，proxy是中间函数，只是为了符合
    //pthread_create函数的定义
    class Thread
    {
        protected:
            pthread_t pid;
        public:
            virtual void run() {};
            static void *proxy(void *args)
            {
                Thread *thread = (Thread *)args;
                thread->run();
                return NULL;
            }
            void start() {pthread_create(&pid, NULL, proxy, this);};
            void join() {pthread_join(pid, NULL);};
    };
}

#endif

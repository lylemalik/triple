#ifndef __THREAD_WORKTHREAD_H__
#define __THREAD_WORKTHREAD_H__

#include <thread/mutex.h>
#include <thread/cond.h>
#include <thread/job.h>
#include <thread/thread.h>
#include <thread/pool.h>
using namespace std;
namespace triple
{
    class Pool;
    class Workthread:public Thread
    {
        private:
            Pool *pool;
            Job *job;
            void *job_data;
            Mutex *mutex;
            Cond *cond;
        public:
            Workthread();
            Workthread(Pool *pool);
            ~Workthread();
            void run();
            void exit();
            void set_pool(Pool *pool);
            void set_job(Job *job, void *job_data);
    };
}

#endif

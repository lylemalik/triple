#ifndef __WORKTHREAD_H__
#define __WORKTHREAD_H__

#include <mutex.h>
#include <cond.h>
#include <job.h>
#include <thread.h>
#include <pool.h>
using namespace std;
namespace triple
{
    class Pool;
    //真正执行任务的线程，通过设定任务和任务参数告诉线程的工作，死循环保证线程不会退出
    //通过把job置空，并通知线程的方法，让线程退出
    class Workthread:public Thread
    {
        private:
            Pool *pool;
            Job *job;
            void *job_data;
            Mutex *job_mutex;
            Cond *job_cond;
        public:
            Workthread() {};
            Workthread(Pool *pool);
            ~Workthread();
            void run();
            void exit();
            void set_job(Job *job, void *job_data);
    };
}

#endif

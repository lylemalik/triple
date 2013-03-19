#ifndef __THREAD_POOL_H__
#define __THREAD_POOL_H__

#include <thread/mutex.h>
#include <thread/cond.h>
#include <thread/job.h>
#include <thread/workthread.h>
#include <queue>
#include <algorithm>
using namespace std;
namespace triple
{
    class Workthread;
    class Pool
    {
        private:
            int size;
            queue<Workthread *> *thread_list;
            queue<Workthread *> *busy_list;
            queue<Workthread *> *idle_list;
            Mutex *busy_mutex;
            Mutex *idle_mutex;
            Cond *busy_cond;
            Cond *idle_cond;
        public:
            Pool() {};
            Pool(int size);
            ~Pool();
            void run(Job *job, void *job_data);
            void move_to_idle_list(Workthread *wt);
            void move_to_busy_list(Workthread *wt);
            Workthread *get_idle_thread();
            void terminate();
            queue<Workthread *> *get_idle_list();
    };
}
#endif

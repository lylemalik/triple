#ifndef __THREAD_POOL_H__
#define __THREAD_POOL_H__

#include <thread/mutex.h>
#include <thread/cond.h>
#include <thread/job.h>
#include <thread/workthread.h>
#include <vector>
#include <algorithm>
using namespace std;
#define THREAD_NUM 4
namespace triple
{
    class Workthread;
    class Pool
    {
        private:
            int size;
            vector<Workthread *> *thread_list;
            vector<Workthread *> *busy_list;
            vector<Workthread *> *idle_list;
            Mutex *busy_mutex;
            Mutex *idle_mutex;
            Cond *busy_cond;
            Cond *idle_cond;
        public:
            Pool();
            Pool(int size);
            ~Pool();
            void run(Job *job, void *job_data);
            void move_to_idle_list(Workthread *wt);
            void move_to_busy_list(Workthread *wt);
            Workthread *get_idle_thread();
            void terminate();
            vector<Workthread *> *get_idle_list();
    };
}
#endif

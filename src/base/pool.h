#ifndef __POOL_H__
#define __POOL_H__

#include <deque>
#include <mutex.h>
#include <cond.h>
#include <workthread.h>
#include <job.h>

using namespace std;
namespace triple
{
    class Workthread;
    class Pool
    {
        private:
            int size;
            deque<Workthread *> *thread_que;
            deque<Workthread *> *idle_que;
            deque<Workthread *> *busy_que;
            Mutex *busy_mutex;
            Mutex *idle_mutex;
            Cond *busy_cond;
            Cond *idle_cond;
        public:
            Pool() {};
            Pool(int size);
            ~Pool();
            void run(Job *job, void *job_data);
            void move_to_idle_que(Workthread *wt);
            void move_to_busy_que(Workthread *wt);
            Workthread *get_idle_thread();
            void terminate();
    };
}

#endif

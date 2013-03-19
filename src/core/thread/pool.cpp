#include <thread/pool.h>
#include <thread/mutex.h>
#include <thread/cond.h>
#include <thread/job.h>
#include <thread/workthread.h>
#include <iostream>
#include <queue>
using namespace std;
using namespace triple;

Pool::Pool(int size)
{
    this->size = size;
    thread_list = new queue<Workthread *>;
    busy_list = new queue<Workthread *>;
    idle_list = new queue<Workthread *>;
    busy_mutex = new Mutex();
    idle_mutex = new Mutex();
    busy_cond = new Cond();
    idle_cond = new Cond();

    for (int i = 0; i < size ; ++i)
    {
        Workthread *wt = new Workthread(this);
        thread_list->push(wt);
        idle_list->push(wt);
        wt->start();
    }
}

Pool::~Pool()
{
    terminate();
    delete(thread_list);
    delete(busy_list);
    delete(idle_list);
    delete(busy_mutex);
    delete(idle_mutex);
    delete(busy_cond);
    delete(idle_cond);
}

void Pool::terminate()
{
    while (thread_list->size())
    {
        Workthread *wt = thread_list->front();
        thread_list->pop();
        wt->exit();
        wt->join();
        delete(wt);
    }
}

void Pool::move_to_busy_list(Workthread *wt)
{
    busy_mutex->lock();
    busy_list->push(wt);
    busy_mutex->unlock();
}

void Pool::move_to_idle_list(Workthread *wt)
{
    idle_mutex->lock();
    idle_list->push(wt);
    idle_mutex->unlock();
}

Workthread *Pool::get_idle_thread()
{
    idle_mutex->lock();
    while (idle_list->size() <= 0)
        idle_cond->wait(idle_mutex);
    if (idle_list->size() > 0)
    {
        Workthread *wt = idle_list->front();
        idle_list->pop();
        idle_mutex->unlock();
        return wt;
    }
    idle_mutex->unlock();
    return NULL;
}

void Pool::run(Job *job, void *job_data)
{
    Workthread *wt = get_idle_thread();
    if (wt)
    {
        move_to_busy_list(wt);
        wt->set_job(job, job_data);
    }
}

#include <thread/workthread.h>
#include <thread/mutex.h>
#include <thread/cond.h>
#include <thread/job.h>
#include <thread/thread.h>
#include <thread/pool.h>
#include <iostream>

using namespace std;
using namespace triple;

Workthread::Workthread()
{
    this->pool = NULL;
    job = NULL;
    job_data = NULL;
    mutex = new Mutex();
    cond = new Cond();
}

Workthread::Workthread(Pool *pool)
{
    this->pool = pool;
    job = NULL;
    job_data = NULL;
    mutex = new Mutex();
    cond = new Cond();
}

Workthread::~Workthread()
{
    delete(mutex);
    delete(cond);
}

void Workthread::set_pool(Pool *pool)
{
    this->pool = pool;
}

void Workthread::exit()
{
    cond->singal();
}

void Workthread::run()
{
    while (1)
    {
        mutex->lock();
        if (job == NULL)
            cond->wait(mutex);
        if (job)
            job->run(job_data);
        else
            pthread_exit(NULL);
        job = NULL;
        mutex->unlock();
        pool->move_to_idle_list(this);
    }
}

void Workthread::set_job(Job *job, void *job_data)
{
    mutex->lock();
    this->job = job;
    this->job_data = job_data;
    mutex->unlock();
    cond->singal();
}

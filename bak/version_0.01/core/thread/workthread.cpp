#include <thread/workthread.h>
#include <thread/mutex.h>
#include <thread/cond.h>
#include <thread/job.h>
#include <thread/thread.h>
#include <thread/pool.h>
#include <iostream>

using namespace std;
using namespace triple;

Workthread::Workthread(Pool *pool)
{
    this->pool = pool;
    job = NULL;
    job_data = NULL;
    job_mutex = new Mutex();
    job_cond = new Cond();
}

Workthread::~Workthread()
{
    delete(job_mutex);
    delete(job_cond);
}

void Workthread::exit()
{
    job_cond->singal();
}

void Workthread::run()
{
    while (1)
    {
        job_mutex->lock();
        if (job == NULL)
            job_cond->wait(job_mutex);
        if (job)
            job->run(job_data);
        else
            pthread_exit(NULL);
        job = NULL;
        job_mutex->unlock();
        pool->move_to_idle_list(this);
    }
}

void Workthread::set_job(Job *job, void *job_data)
{
    job_mutex->lock();
    this->job = job;
    this->job_data = job_data;
    job_mutex->unlock();
    job_cond->singal();
}

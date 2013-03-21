#include <workthread.h>
using namespace std;
using namespace triple;

Workthread::Workthread(Pool *pool)
{
    this->job = NULL;
    this->pool = pool;
    this->job_mutex = new Mutex();
    this->job_cond = new Cond();
}

Workthread::~Workthread()
{
    delete(job_mutex);
    delete(job_cond);
}

void Workthread::run()
{
    while (1)
    {
        job_mutex->lock();
        if (job == NULL)
            job_cond->wait(job_mutex); //退出线程的时候，会调用singal，设置了任务的时候也会调用singal，
                              //如果job仍然为空，那么就是退出，不为空则执行任务
        if (job)
            job->run(job_data);
        else
            pthread_exit(NULL);
        //任务执行完毕，把job置空，否则死循环
        job = NULL;
        job_mutex->unlock();
        //重新移动到空闲队列
        pool->move_to_idle_que(this);
    }
}

void Workthread::set_job(Job *job, void *job_data)
{
    job_mutex->lock();
    this->job = job;
    this->job_data = job_data;
    job_mutex->unlock();
    //通知run 函数，job已经设定好，开始执行任务
    job_cond->singal();
}

void Workthread::exit()
{
    //没有设置任务，调用此函数，则线程检测到会退出
    job_cond->singal();
}

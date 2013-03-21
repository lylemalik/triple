#include <pool.h>
#include <algorithm>
#include <iostream>
using namespace std;
using namespace triple;

Pool::Pool(int size)
{
    this->size = size;
    thread_que = new deque<Workthread *>;
    idle_que = new deque<Workthread *>;
    busy_que = new deque<Workthread *>;
    busy_mutex = new Mutex();
    busy_cond = new Cond();
    idle_mutex = new Mutex();
    idle_cond = new Cond();

    for (int i = 0; i < size; i++)
    {
        Workthread *wt = new Workthread(this);
        thread_que->push_back(wt);
        idle_que->push_back(wt);
        wt->start();
    }
}

Pool::~Pool()
{
    terminate();
    delete(thread_que);
    delete(idle_que);
    delete(busy_que);
    delete(busy_mutex);
    delete(busy_cond);
    delete(idle_mutex);
    delete(idle_cond);
}

void Pool::terminate()
{
    while (thread_que->size())
    {
        Workthread *wt = thread_que->front();
        thread_que->pop_front();
        wt->exit();
        wt->join();
        delete(wt);
    }
}

void Pool::run(Job *job, void *job_data)
{
    Workthread *wt = get_idle_thread();
    move_to_busy_que(wt);
    //设置任务后，工作线程就会进行
    wt->set_job(job, job_data);
}

void Pool::move_to_busy_que(Workthread *wt)
{
    busy_mutex->lock();
    busy_que->push_back(wt);
    busy_mutex->unlock();
}

void Pool::move_to_idle_que(Workthread *wt)
{
    //先要删除busy_que里面的wt，因为在workthread里面删除不方便
    deque<Workthread *>::iterator iter
        = find(busy_que->begin(), busy_que->end(), wt);
    if (iter != busy_que->end())
        busy_que->erase(iter);

    idle_mutex->lock();
    idle_que->push_back(wt);
    idle_mutex->unlock();
    //空闲队列有元素后，通知阻塞的线程
    idle_cond->singal();
}

Workthread *Pool::get_idle_thread()
{
    idle_mutex->lock();
    while (idle_que->size() <= 0)
        idle_cond->wait(idle_mutex);
    Workthread *wt = idle_que->front();
    idle_que->pop_front();
    idle_mutex->unlock();
    return wt;
}

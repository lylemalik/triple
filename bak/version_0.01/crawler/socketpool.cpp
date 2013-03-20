#include <iostream>
#include <socketpool.h>
#include <deque>
#include <vector>
using namespace std;
using namespace triple;

Socketpool::Socketpool(int socketnum, string host)
{
    net_que = new deque<Net *>;
    idle_que = new deque<Net *>;
    busy_que = new deque<Net *>;
    busy_mutex = new Mutex();
    idle_mutex = new Mutex();
    busy_cond = new Cond();
    idle_cond = new Cond();
    for (int i = 0; i < socketnum; i++)
    {
        Net *net = new Net(host);
        net_que->push_back(net);
        idle_que->push_back(net);
        net->link();
    }
}

Socketpool::~Socketpool()
{
    while (net_que->size())
    {
        delete(net_que->front());
        net_que->pop_front();
    }
    delete(net_que);
    delete(idle_que);
    delete(busy_que);
    delete(busy_mutex);
    delete(idle_mutex);
    delete(busy_cond);
    delete(idle_cond);
}

Net *Socketpool::get_idle_socket()
{
    idle_mutex->lock();
    while (idle_que->size() <= 0)
        idle_cond->wait(idle_mutex);
    Net *net = idle_que->front();
    idle_que->pop_front();
    idle_mutex->unlock();
    return net;
}

void Socketpool::move_to_idle_que(Net *net)
{
    idle_mutex->lock();
    idle_que->push_back(net);
    idle_mutex->unlock();
    idle_cond->singal();
}

void Socketpool::move_to_busy_que(Net *net)
{
    busy_mutex->lock();
    busy_que->push_back(net);
    busy_mutex->unlock();
}

#include <socketpool.h>
#include <queue>
#include <vector>

Socketpool::Socketpool()
{
    net_vec = new vector<Net *>;
    idle_que = new queue<Net *>;
    busy_que = new queue<Net *>;
    busy_mutex = new Mutex();
    idle_mutex = new Mutex();
    busy_cond = new Cond();
    idle_cond = new Cond();
}

Socketpool::Socketpool(int socketnum, string host, int port)
{
    net_vec = new vector<Net *>;
    idle_que = new queue<Net *>;
    busy_que = new queue<Net *>;
    busy_mutex = new Mutex();
    idle_mutex = new Mutex();
    busy_cond = new Cond();
    idle_cond = new Cond();
    for (int i = 0; i < socketnum; i++)
    {
        Net *net = new Net(host, port);
        net_vec->push_back(net);
        idle_que->push(net);
    }
}

Socketpool::~Socketpool()
{
    for (int i = 0; i < net_vec->size(); i++)
        delete((*net_vec)[i]);
    delete(net_vec);
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
    Net *net = idle_que->pop();
    idle_mutex->unlock();
}

void Socketpool::move_to_idle_que(Net *net)
{
    idle_mutex->lock();
    idle_que->push(net);
    idle_mutex->unlock();
}

void Socketpool::move_to_busy_que(Net *net)
{
    busy_mutex->lock();
    busy_que->push(net);
    busy_que->unlock();
}

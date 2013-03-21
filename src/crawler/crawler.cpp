#include <iostream>
#include <stdlib.h>
#include <crawler.h>
#include <pool.h>
#include <resjob.h>
#include <reqthread.h>
using namespace std;
using namespace triple;

Crawler::Crawler()
{
    this->site_vec = new vector<Site *>;
    this->site_mutex = new Mutex();
    this->iter_mutex = new Mutex();
    this->site_iter = -1;
    this->epollfd = epoll_create(MAX_EVENT);
    this->pool = new Pool(THREAD_NUM);
}

Crawler::~Crawler()
{
    delete(site_vec);
    delete(site_mutex);
    delete(iter_mutex);
    delete(pool);
}

Site *Crawler::get_next_site()
{
    iter_mutex->lock();
    site_iter++;
    if (site_vec->size() <= site_iter)
    {
        site_iter = site_iter % site_vec->size();
        sleep(0.3);
    }
    iter_mutex->unlock();
    return (*site_vec)[site_iter];
}

Site *Crawler::add_site(string host)
{
    Site *site = new Site(host);
    site_mutex->lock();
    site_vec->push_back(site);
    site_mutex->unlock();
    return site;
}

void Crawler::start()
{
    add_site("www.hust.edu.cn");
    Reqthread *reqthread = new Reqthread(this);
    reqthread->start();
    while (1)
    {
        struct epoll_event events[MAX_EVENT];
        int ready = epoll_wait(epollfd, events, MAX_EVENT, TIMEOUT);
        if (ready <= 0)
            continue;
        for (int i = 0; i < ready; i++)
        {
            Resjob *resjob = new Resjob(this);
            epoll_ctl(epollfd, EPOLL_CTL_DEL, ((Epoll_ptr *)events[i].data.ptr)->net->get_sockfd(), NULL);
            pool->run(resjob, events[i].data.ptr);
        }
    }
}

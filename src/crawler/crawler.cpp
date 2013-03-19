#include <iostream>
#include <crawler.h>
#include <site.h>
#include <vector>
#include <sys/epoll.h>
#include <requester.h>
#include <thread/pool.h>
#include <responsejob.h>

using namespace std;
using namespace triple;

Crawler::Crawler()
{
    site_que = new deque<Site *>;
    epollfd = epoll_create(MAXEVENT);
    site_que_mutex = new Mutex();
}

void Crawler::start()
{
    add_site("www.hust.edu.cn");
    Requester *requester = new Requester(this);
    requester->start();
    
    Pool *pool = new Pool(1);

    struct epoll_event events[MAXEVENT];
    while (1)
    {
        int ready = epoll_wait(epollfd, events, MAXEVENT, 10);
        if (ready <= 0)
            continue;
        cout << "ready = " << ready << endl;
        for (int i = 0; i < ready; i++)
        {
            Responsejob *rjob = new Responsejob(this);
            pool->run(rjob, events[i].data.ptr);
            epoll_ctl(epollfd, EPOLL_CTL_DEL, ((Epoll_ptr *)events[i].data.ptr)->net->get_sockfd(), NULL);
        }
    }
}

Site *Crawler::add_site(string host)
{
    Site *site = new Site(host);
    site_que_mutex->lock();
    site_que->push_back(site);
    site_que_mutex->unlock();
    site->push_being_fetch(host);
    return site;
}

deque<Site *> *Crawler::get_site_que()
{
    return site_que;
}

int Crawler::get_epollfd()
{
    return epollfd;
}

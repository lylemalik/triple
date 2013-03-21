#ifndef __CRAWLER_H__
#define __CRAWLER_H__

#include <site.h>
#include <vector>
#include <mutex.h>
#include <sys/epoll.h>
#include <config.h>
#include <pool.h>
using namespace std;
namespace triple
{
    class Crawler
    {
        private:
            vector<Site *> *site_vec;
            Mutex *site_mutex;
            Mutex *iter_mutex;
            unsigned site_iter; //site_vec的迭代器，因为每次都会从不同的site取URL 
            int epollfd;
            //int unfetch_num; //当这个值为0，并且线程池的线程全部为空闲的时候，停止爬虫 
            Pool *pool;
        public:
            Crawler();
            ~Crawler();
            void start();
            int get_epollfd() {return epollfd;}
            //int get_unfetch_num() {return unfetch_num;}
            Pool *get_pool() {return pool;}
            Site *get_next_site();
            Site *add_site(string host);
            vector<Site *> *get_site_vec() {return site_vec;}
    };
}

#endif

#ifndef __CRAWLER_H__
#define __CRAWLER_H__

#include <site.h>
#include <deque>
#include <thread/mutex.h>
using namespace std;

#define MAXEVENT 1024
#define AVALROOT "hust.edu.cn"
#define THREADNUM 3
namespace triple
{
    class Crawler
    {
        private:
            deque<Site *> *site_que;
            int epollfd;
            Mutex *site_que_mutex;
        public:
            Crawler();
            void start();
            Site *add_site(string host);
            deque<Site *> *get_site_que();
            int get_epollfd();
    };
}

#endif

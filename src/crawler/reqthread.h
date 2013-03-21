#ifndef __REQTHREAD_H__
#define __REQTHREAD_H__

#include <thread.h>
#include <crawler.h>
#include <net.h>
#include <string>
using namespace std;
namespace triple
{
    //继承自thread基类，工作是从site_vec里面找出合适的site
    //并且取出URL，发送http请求，交给epoll处理
    class Reqthread:public Thread
    {
        private:
            Crawler *crawler;
        public:
            Reqthread() {};
            Reqthread(Crawler *crawler);
            void run();
    };

    class Epoll_ptr
    {
        public:
            Net *net;
            string url;
    };
}

#endif

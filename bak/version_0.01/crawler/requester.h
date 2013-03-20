#ifndef __REQUESTER_H__
#define __REQUESTER_H__

#include <thread/thread.h>
#include <crawler.h>
#include <socketpool.h>
using namespace std;
#define SOCKETNUM 1
#define PORT 80
namespace triple
{
    class Crawler;
    class Requester:public Thread
    {
        private:
            Crawler *crawler;
        public:
            Requester() {};
            Requester(Crawler *crawler);
            ~Requester();
            int http_requester(Net *net, string url);
            void run();
    };

    class Epoll_ptr
    {
        public:
            Net *net;
            string url;
            Socketpool *socketpool;
    };
}

#endif

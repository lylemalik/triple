#ifndef __REQUESTER_H__
#define __REQUESTER_H__

#include <thread/thread.h>
#include <crawler.h>
using namespace std;
#define SOCKETNUM 3
#define PORT 80
namespace triple
{
    class Crawler;
    class Requester:public Thread
    {
        private:
            Crawler *crawler;
        public:
            Requester();
            Requester(Crawler *crawler);
            ~Requester();
            void run();
    };
}

#endif

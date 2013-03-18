#ifndef __SOCKETPOOL_H__
#define __SOCKETPOOL_H__

#include <net.h>
#include <string>
#include <queue>
#include <vector>
#include <thread/mutex.h>
#include <thread/cond.h>
using namespace std;

namespace triple
{
    class Socketpool
    {
        private:
            vector<Net *> *net_vec;
            queue<Net *> *busy_que;
            queue<Net *> *idle_que;
            Mutex *busy_mutex;
            Mutex *idle_mutex;
            Cond *busy_cond;
            Cond *idle_cond;
        public:
            Socketpool();
            Socketpool(int socketnum, string host, int port);
            ~Socketpool();
            Net *get_idle_socket();
    };
}
#endif

#ifndef __SOCKETPOOL_H__
#define __SOCKETPOOL_H__

#include <net.h>
#include <string>
#include <deque>
#include <thread/mutex.h>
#include <thread/cond.h>
using namespace std;

namespace triple
{
    class Socketpool
    {
        private:
            deque<Net *> *net_que;
            deque<Net *> *busy_que;
            deque<Net *> *idle_que;
            Mutex *busy_mutex;
            Mutex *idle_mutex;
            Cond *busy_cond;
            Cond *idle_cond;
        public:
            Socketpool() {};
            Socketpool(int socketnum, string host);
            ~Socketpool();
            Net *get_idle_socket();
            void move_to_idle_que(Net *net);
            void move_to_busy_que(Net *net);
    };
}
#endif

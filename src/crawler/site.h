#ifndef __SITE_H__
#define __SITE_H__

#include <string>
#include <deque>
#include <set>
#include <net.h>
#include <thread/mutex.h>
#include <thread/cond.h>

#define PORT 80
using namespace std;
namespace triple
{
    class Site
    {
        private:
            string host;
            deque<string> *being_fetch;
            set<string> *fetched;
            Mutex *being_fetch_mutex;
            Cond *being_fetch_cond;
            Mutex *fetched_mutex;
        public:
            Site() {};
            Site(string host);
            ~Site();
            string get_host();
            deque<string> *get_being_fetch();
            set<string> *get_fetched();
            int is_url_exist(string url);
            void push_being_fetch(string url);
            void push_fetched(string url);
            string pop_url();
    };
}

#endif

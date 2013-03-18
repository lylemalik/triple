#ifndef __SITE_H__
#define __SITE_H__

#include <string>
#include <queue>
#include <set>
#include <net.h>
#include <thread/mutex.h>
using namespace std;
namespace triple
{
    class Site
    {
        private:
            string domain;
            int port;
            queue<string> *being_fetch;
            set<string> *fetched;
            Mutex *being_fetch_mutex;
            Mutex *fetched_mutex;
        public:
            Site();
            Site(string domain, int port);
            ~Site();
            string get_domain();
            int is_url_exist(string url);
            string pop_url();
            void push_being_fetch(string url);
            void push_fetched(string url);
    };
}

#endif

#ifndef __SITE_H__
#define __SITE_H__

#include <string>
#include <deque>
#include <mutex.h>
#include <cond.h>
#include <set>
using namespace std;
namespace triple
{
    class Site
    {
        private:
            string host;
            deque<string> *unfetch;
            set<string> *fetched;
            Mutex *unfetch_mutex;
            Mutex *fetched_mutex;
        public:
            Site() {};
            Site(string host);
            ~Site();
            string get_host() {return host;}
            deque<string> *get_unfetch() {return unfetch;}
            set<string> *get_fetched() {return fetched;}
            string pop_unfetch();
            void push_unfetch(string url);
            void push_fetched(string url);
            int is_url_exist(string url);
    };
}

#endif

#ifndef __CRAWLER_H__
#define __CRAWLER_H__

#include <site.h>
#include <vector>
using namespace std;
#define MAXEVENT 1024
#define AVALROOT "hust.edu.cn"
namespace triple
{
    class Crawler
    {
        private:
            vector<Site *> *site_vec;
        public:
            Crawler();
            void start();
            void add_site(string domain);
    };
}

#endif

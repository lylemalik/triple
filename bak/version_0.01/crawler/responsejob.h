#ifndef __RESPONSE_H__
#define __RESPONSE_H__

#include <thread/job.h>
#include <crawler.h>
#include <deque>
using namespace std;
namespace triple
{
    class Crawler;
    class Responsejob:public Job
    {
        private:
            Crawler *crawler;
        public:
            Responsejob() {};
            Responsejob(Crawler *crawler);
            void run(void *job_data);
            deque<string> *get_link(string web_content, string host);
            void assign_site(deque<string> *link);
    };
}

#endif

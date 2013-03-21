#ifndef __RESJOB_H__
#define __RESJOB_H__

#include <crawler.h>
#include <job.h>
using namespace std;
namespace triple
{
    class Resjob:public Job
    {
        private:
            Crawler *crawler;
        public:
            Resjob() {};
            Resjob(Crawler *crawler);
            void run(void *data);
    };
}

#endif

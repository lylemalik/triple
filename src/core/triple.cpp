#include <iostream>
#include <fstream>
#include <vector>
#include <pregex.h>
#include <config.h>
#include <thread/job.h>
#include <thread/pool.h>
#include <thread/mutex.h>
using namespace std;
using namespace triple;

namespace triple
{
    class xjob:public Job
    {
        public:
            void run(void *job_data);
    };
}

Mutex mutex;

void xjob::run(void *job_data)
{
    mutex.lock();
    cout << "I'm from xjob" << endl;
    mutex.unlock();
}

int main(int argc, const char *argv[])
{
    Pool *pool = new Pool(4);
    for (int i = 0; i < 30; ++i)
    {
        xjob *job = new xjob();
        pool->run(job, NULL);
        delete(job);
    }
    sleep(1);
    pool->terminate();
    delete(pool);
    return 0;
}

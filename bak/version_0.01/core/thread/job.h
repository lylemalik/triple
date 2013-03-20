#ifndef __THREAD_JOB_H__
#define __THREAD_JOB_H__

using namespace std;
namespace triple
{
    class Job
    {
        public:
            virtual void run(void *data){};
    };
}

#endif

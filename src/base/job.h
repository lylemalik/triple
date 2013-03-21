#ifndef __JOB_H__
#define __JOB_H__

using namespace std;
namespace triple
{
    //任务基类，线程池中执行的任务必须从此类继承，实现run方法即可
    class Job
    {
        public:
            virtual void run(void *data) {};
    };
}

#endif

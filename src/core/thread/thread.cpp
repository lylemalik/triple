#include <pthread.h>
#include <thread/thread.h>

using namespace std;
using namespace triple;

void Thread::start()
{
    pthread_create(&pid, NULL, proxy, (void *)this);
}

void *Thread::proxy(void *args)
{
    Thread *thread = (Thread *)args;
    thread->run();
    return NULL;
}

pthread_t Thread::get_pid()
{
    return pid;
}

void Thread::join()
{
    pthread_join(pid, NULL);
}

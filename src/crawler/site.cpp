#include <site.h>
#include <algorithm>
using namespace std;
using namespace triple;

Site::Site(string host)
{
    this->host = host;
    this->unfetch = new deque<string>;
    this->fetched = new set<string>;
    this->unfetch_mutex = new Mutex();
    this->fetched_mutex = new Mutex();
    push_unfetch(host);
}

Site::~Site()
{
    delete(unfetch);
    delete(fetched);
    delete(unfetch_mutex);
    delete(fetched_mutex);
}

//提取一个待抓取的URL
string Site::pop_unfetch()
{
    unfetch_mutex->lock();
    if (unfetch->size())
    {
        string url = unfetch->front();
        unfetch->pop_front();
        unfetch_mutex->unlock();
        return url;
    }
    unfetch_mutex->unlock();
    return "";
}

void Site::push_unfetch(string url)
{
    unfetch_mutex->lock();
    unfetch->push_back(url);
    unfetch_mutex->unlock();
}

void Site::push_fetched(string url)
{
    fetched_mutex->lock();
    fetched->insert(url);
    fetched_mutex->unlock();
}

//判断URL是否已经存在了，不仅是已经抓取过的SET，
//还有正准备抓的deque，两个都不存在这个URL则添加
int Site::is_url_exist(string url)
{
    unfetch_mutex->lock();
    fetched_mutex->lock();
    deque<string>::iterator uiter
        = find(unfetch->begin(), unfetch->end(), url);
    set<string>::iterator diter = fetched->find(url);
    unfetch_mutex->unlock();
    fetched_mutex->unlock();
    if (uiter != unfetch->end() || diter != fetched->end())
        return 1;
    return 0;
}

#include <iostream>
#include <site.h>
#include <string>
#include <set>
#include <net.h>
#include <algorithm>
using namespace std;
using namespace triple;

Site::Site(string host)
{
    this->host = host;
    being_fetch = new deque<string>;
    fetched = new set<string>;
    being_fetch_mutex = new Mutex();
    being_fetch_cond = new Cond();
    fetched_mutex = new Mutex();
}

Site::~Site()
{
    delete(being_fetch);
    delete(fetched);
    delete(being_fetch_mutex);
    delete(being_fetch_cond);
    delete(fetched_mutex);
}

string Site::get_host()
{
    return host;
}

deque<string> *Site::get_being_fetch()
{
    return being_fetch;
}

set<string> *Site::get_fetched()
{
    return fetched;
}

int Site::is_url_exist(string url)
{
    set<string>::iterator iter;
    fetched_mutex->lock();
    iter = fetched->find(url);
    fetched_mutex->unlock();

    deque<string>::iterator diter;
    being_fetch_mutex->lock();
    diter = find(being_fetch->begin(), being_fetch->end(), url);
    being_fetch_mutex->unlock();

    if (iter != fetched->end() || diter != being_fetch->end())
        return 1;
    return 0;
}

string Site::pop_url()
{
    string url;
    being_fetch_mutex->lock();
    if (being_fetch->size() <= 0)
        being_fetch_cond->wait(being_fetch_mutex);
    if (being_fetch->size() <= 0)
    {
        being_fetch_mutex->unlock();
        return NULL;
    }
    url = being_fetch->front();
    being_fetch->pop_front();
    being_fetch_mutex->unlock();
    return url;
}

void Site::push_being_fetch(string url)
{
    being_fetch_mutex->lock();
    being_fetch->push_back(url);
    being_fetch_mutex->unlock();
    being_fetch_cond->singal();
}

void Site::push_fetched(string url)
{
    fetched_mutex->lock();
    fetched->insert(url);
    fetched_mutex->unlock();
}

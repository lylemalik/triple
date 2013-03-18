#include <site.h>
#include <string>
#include <set>
#include <net.h>
using namespace std;
using namespace triple;

Site::Site()
{
    being_fetch = new vector<string>;
    fetched = new set<string>;
    being_fetch_mutex = new Mutex();
    fetched_mutex = new Mutex();
}

Site::Site(string domain, int port)
{
    this->domain = domain;
    this->port = port;
    being_fetch = new vector<string>;
    fetched = new set<string>;
    being_fetch_mutex = new Mutex();
    fetched_mutex = new Mutex();
}

~Site::Site()
{
    delete(being_fetch);
    delete(fetched);
    delete(being_fetch_mutex);
    delete(fetched_mutex);
}

string Site::get_domain()
{
    return domain;
}

int Site::is_url_exist(string url)
{
    set<string>::iterator iter;
    iter = fetched->find(url);
    if (iter != fetched->end())
        return 1;
    return 0;
}

string Site::pop_url()
{
    string url;
    being_fetch_mutex->lock();
    if (being_fetch->size() > 0)
        url = being_fetch->pop();
    being_fetch_mutex->unlock();
    return url;
}

void Site::push_being_fetch(string url)
{
    being_fetch_mutex->lock();
    being_fetch->push(url);
    being_fetch_mutex->unlock();
}

void Site::push_fetched(string url)
{
    fetched_mutex->lock();
    fetched->insert(url);
    fetched_mutex->unlock();
}

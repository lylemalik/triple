#include <crawler.h>
#include <site.h>
#include <vector>
#include <sys/epoll.h>
#include <requester.h>

using namespace std;
using namespace triple;

Crawler::Crawler()
{
    site_vec = new vector<Site *>;
}

void Crawler::start()
{
    add_site("www.hust.edu.cn");
    int epollfd = epoll_create(MAXEVENT);
    Requester *requester = new Requester(this);
    requester->start();
}

void Crawler::add_site(string domain)
{
    Site *site = new Site(domain);
    site_vec->push_back(site);
}

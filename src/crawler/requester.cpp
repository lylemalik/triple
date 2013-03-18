#include <requester.h>
#include <thread/thread.h>
#include <net.h>
#include <crawler.h>

Requester::Requester()
{
    crawler = 0;
}

Requester::Requester(Crawler *crawler)
{
    this->crawler = crawler;
}

Requester::~Requester()
{
    crawler = 0;
}

void Requester::run()
{
    int iter = 0;
    while (1)
    {
        if (crawler->site_vec->size() <= iter)
            break;
        Site *site = (*crawler->site_vec)[iter];
        Socketpool *pool = new Socketpool(SOCKETNUM, site->domain, site->port);
    }
}

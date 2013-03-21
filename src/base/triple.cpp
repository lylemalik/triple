#include <iostream>
#include <pool.h>
#include <job.h>
#include <config.h>
#include <net.h>
#include <dns.h>
#include <crawler.h>

using namespace std;
using namespace triple;

Dns *Dns::dns = NULL;
int main(int argc, const char *argv[])
{
    Crawler *crawler = new Crawler();
    crawler->start();
    return 0;
}

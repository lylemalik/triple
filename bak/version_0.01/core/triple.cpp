#include <iostream>
#include <vector>
#include <regex.h>
#include <thread/pool.h>
#include <crawler.h>
#include <dns.h>
using namespace std;
using namespace triple;

Dns *Dns::dns = NULL;
int main(int argc, const char *argv[])
{
    Crawler *crawler = new Crawler();
    crawler->start();
    return 0;
}

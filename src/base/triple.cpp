#include <iostream>
#include <pool.h>
#include <job.h>
#include <config.h>
#include <net.h>
#include <dns.h>
#include <crawler.h>
#include <index.h>
#include <segment.h>

using namespace std;
using namespace triple;

Dns *Dns::dns = NULL;
Segment *Segment::seg = NULL;
int main(int argc, const char *argv[])
{
    Index *index = new Index();
    index->start();
    return 0;
}

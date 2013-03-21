#include <dns.h>
#include <netdb.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

using namespace std;
using namespace triple;

string Dns::get_ip_by_host(string host)
{
    map <string, string>::iterator iter;
    iter = dnsmap.find(host);
    if (iter != dnsmap.end())
        return iter->second;
    else
    {
        struct hostent *ent = gethostbyname(host.c_str());
        if (ent == NULL)
            return "";
        char *cip = inet_ntoa( *(struct in_addr *)ent->h_addr);
        string ip = cip;
        dnsmap.insert(map<string,string>::value_type (host, ip));
        return ip;
    }
}

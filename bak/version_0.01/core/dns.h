#ifndef __DNS_H__
#define __DNS_H__

#include <map>
#include <string>
using namespace std;
namespace triple
{
    class Dns
    {
        private:
            Dns(){};
            static Dns *dns;
            map<string, string> dnsmap;
        public:
            static Dns *get_instance()
            {
                if (dns == NULL)
                    dns = new Dns();
                return dns;
            }
            string get_ip_by_host(string host);
    };
}

#endif

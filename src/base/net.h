#ifndef __NET_H__
#define __NET_H__

#include <string>
using namespace std;
namespace triple
{
    class Net
    {
        private:
            string host;
            int port;
            int sockfd;
            string ip;
        public:
            Net() {};
            Net(string host, int port);
            string receice();
            int post(string content);
            int link();
            void set_non_block();
            int get_sockfd() {return sockfd;}
            string get_host() {return host;}
            string get_ip() {return ip;}
    };
}

#endif

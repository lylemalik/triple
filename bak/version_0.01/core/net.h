#ifndef __NET_H__
#define __NET_H__
#include <string>
using namespace std;
#define MAXLEN 1024
#define PORT 80
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
            Net(string host);
            ~Net() {close(sockfd);}
            //void set_value(string host, int port);
            string receive(int len);
            int post(string content);
            int link();
            int get_sockfd();
            void set_non_block();
            string get_host()
            {
                return host;
            }
    };
}

#endif

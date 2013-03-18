#ifndef __NET_H__
#define __NET_H__
using namespace std;
#define MAXLEN 1024
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
            void set_value(string host, int port);
            string receive(int len);
            int post(string content);
            int link();
            void set_non_block();
    };
}

#endif

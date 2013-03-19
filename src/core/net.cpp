#include <iostream>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <fcntl.h>
#include <string>
#include <string.h>
#include <errno.h>
#include <net.h>
#include <dns.h>

using namespace std;
using namespace triple;

Net::Net(string host)
{
    this->host = host;
    this->sockfd = socket(AF_INET, SOCK_STREAM, 0);
    this->set_non_block();
    Dns *dns = Dns::get_instance();
    this->ip = dns->get_ip_by_host(host);
    this->set_non_block();
}

//void Net::set_value(string host)
//{
    //this->host = host;
    //this->sockfd = socket(AF_INET, SOCK_STREAM, 0);
    //this->set_non_block();
    //Dns *dns = Dns::get_instance();
    //this->ip = dns->get_ip_by_host(host);
    //this->set_non_block();
//}

void Net::set_non_block()
{
    fcntl(this->sockfd, F_SETFL, (fcntl(this->sockfd, F_GETFL) | O_NONBLOCK));
}

int Net::link()
{
    struct sockaddr_in addr;
    memset(&addr, 0, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = inet_addr(ip.c_str());
    addr.sin_port = htons(PORT);
    if (connect(sockfd, (struct sockaddr *)&addr, sizeof(struct sockaddr)) == 0)
        return 1;
    if (errno == EINPROGRESS)
    {
        fd_set wfds;
        struct timeval tv;
        int retval;
        FD_ZERO(&wfds);
        FD_SET(sockfd, &wfds);
        tv.tv_sec = 1;
        tv.tv_usec = 0;
        retval = select(sockfd + 1, NULL, &wfds, NULL, &tv);
        if (retval)
            return 1;
        else
        {
            close(sockfd);
            return -1;
        }
    }
    else
    {
        close(sockfd);
        return -1;
    }
}

string Net::receive(int len)
{
    string content;
    char read_buf[MAXLEN];
    if (len == -1)
    {
        int temp = 0;
        while (1)
        {
            memset(read_buf, 0, MAXLEN);
            temp = read(sockfd, read_buf, MAXLEN);
            cout << "read, sockfd = " << sockfd << ", len = " << temp << endl;
            if (temp == -1 && errno == EAGAIN)
                continue;
            else if (temp > 0)
                content += read_buf;
            else
                break;
        }
    }
    return content;
}

int Net::post(string content)
{
    int writed_len = 0;
    int buf_len;
    int len = content.length();
    while (writed_len < len)
    {
        buf_len = (len - writed_len > MAXLEN ? MAXLEN : len - writed_len);
        writed_len += write(sockfd, content.c_str() + writed_len, buf_len);
        if (writed_len < 0)
            return -1;
    }
    cout << "write, sockfd = " << sockfd << ", len = " << writed_len << endl;
    return writed_len;
}

int Net::get_sockfd()
{
    return sockfd;
}

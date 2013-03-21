#include <net.h>
#include <iostream>
#include <sys/socket.h>
#include <sys/types.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <fcntl.h>
#include <config.h>
#include <dns.h>
#include <string.h>
#include <errno.h>
using namespace std;
using namespace triple;

Net::Net(string host, int port)
{
    this->host = host;
    this->port = port;
    this->sockfd = socket(AF_INET, SOCK_STREAM, 0);
    this->set_non_block();
    //dns 的单例模式，整个系统都只能有一个DNS解析器
    Dns *dns = Dns::get_instance();
    this->ip = dns->get_ip_by_host(host);
}

void Net::set_non_block()
{
    fcntl(sockfd, F_SETFL, (fcntl(sockfd, F_GETFL) | O_NONBLOCK));
}

string Net::receice()
{
    string content;
    char buf[MAXLEN];
    int temp = 0;
    while (1)
    {
        memset(buf, 0, MAXLEN);
        temp = recv(sockfd, buf, MAXLEN, 0);
        //因为socket是非阻塞的，所以虽然epoll返回可读，但是数据并非全部到达
        //这时，缓冲区读完后，可能暂时为空，继续读取会发生错误，errno=EAGAIN
        //表示数据没有读完，使循环继续，如果返回0，则表示读取完毕
        if (temp == -1 && errno == EAGAIN)
            continue;
        else if (temp > 0)
            content += buf;
        else
            break;
    }
    return content;
}

//TODO:因为目前发送的数据只是http请求，非常短，所以直接发送，
//之后如果有客户端交互，再改为一段一段发送
int Net::post(string content)
{
    return send(sockfd, content.c_str(), content.length(), 0);
}

//TODO:与服务器连接，还要考虑超时情况，用select做超时处理，
//不过这里每次只select一个socket，效果不好，之后再改
int Net::link()
{
    struct sockaddr_in addr;
    memset(&addr, 0, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = inet_addr(ip.c_str());
    addr.sin_port = htons(port);

    if (connect(sockfd, (struct sockaddr *)&addr, sizeof(struct sockaddr)) == 0)
        return 1;
    if (errno == EINPROGRESS)
    {
        //TODO:此处绝对不行。。。。。
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
        close(sockfd);
        return -1;
    }
    close(sockfd);
    return -1;
}

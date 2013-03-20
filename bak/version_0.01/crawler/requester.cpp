#include <iostream>
#include <requester.h>
#include <thread/thread.h>
#include <net.h>
#include <crawler.h>
#include <socketpool.h>
#include <sys/epoll.h>
#include <sys/socket.h>
using namespace std;
using namespace triple;

Requester::Requester(Crawler *crawler)
{
    this->crawler = crawler;
}

Requester::~Requester()
{
    crawler = 0;
}

void Requester::run()
{
    unsigned iter = 0;
    while (1)
    {
        if (crawler->get_site_que()->size() <= iter)
            break;
        Site *site = (*crawler->get_site_que())[iter];
        Socketpool *socketpool = new Socketpool(SOCKETNUM, site->get_host());
        while (1)
        {
            string url = site->pop_url();
            if (url.length() == 0) //这个队列已经完了 
                break;
            site->push_fetched(url);
            Net *net = socketpool->get_idle_socket();
            net->link();
            http_requester(net, url);
            cout << "send request " + url << endl;
            //if (post_ok == -1)
            //{
                //net->link();
                //http_requester(net, url);
            //}
            struct epoll_event ev;
            ev.events = EPOLLIN;
            Epoll_ptr *ptr = new Epoll_ptr();
            ptr->net = net;
            ptr->url = url;
            ptr->socketpool = socketpool;
            ev.data.ptr = ptr;
            epoll_ctl(crawler->get_epollfd(), EPOLL_CTL_ADD, net->get_sockfd(), &ev);
            cout << "sockfd = " << net->get_sockfd() << endl;
        }
        iter++;
    }
}

static string get_host(string url)
{
    int i = 0;
    int len = url.length();
    while (i < len && url[i] != '/' && url[i] != ':')
        i++;
    return string(url, 0, i);
}

static string get_relative_url(string url)
{
    int i = 0;
    int len = url.length();
    while (i < len && url[i] != '/')
        i++;
    if (i == len)
        return string("/");
    return string(url, i, len - i);
}

int Requester::http_requester(Net *net, string url)
{
    string host = get_host(url);
    string relative_url = get_relative_url(url);
    string header = "GET " + relative_url + " HTTP/1.0\r\nHost: " + host + "\r\n\r\n";
    return net->post(header);
}

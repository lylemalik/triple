#include <iostream>
#include <reqthread.h>
#include <helper.h>
#include <site.h>
#include <config.h>
using namespace std;
using namespace triple;

Reqthread::Reqthread(Crawler *crawler)
{
    this->crawler = crawler;
}

static int http_request(Net *net, string url)
{
    string host = get_host(url);
    string relative_url = get_relative_url(url);
    string header = "GET " + relative_url + " HTTP/1.0\r\nHost: " + host + "\r\n\r\n";
    return net->post(header);
}

void Reqthread::run()
{
    while (1)
    {
        Site *site = crawler->get_next_site();
        string url = site->pop_unfetch();
        if (url.length() == 0)
            continue;
        string host = get_host(url);
        Net *net = new Net(host, PORT);
        if (net->get_ip().length() == 0)
            continue;
        if (net->link() == -1)
        {
            delete(net);
            continue;
        }
        if (http_request(net, url) == -1)
        {
            delete(net);
            continue;
        }
        struct epoll_event ev;
        ev.events = EPOLLIN;
        Epoll_ptr *ptr = new Epoll_ptr();
        ptr->url = url;
        ptr->net = net;
        ev.data.ptr = ptr;
        epoll_ctl(crawler->get_epollfd(), EPOLL_CTL_ADD, net->get_sockfd(), &ev);
    }
}

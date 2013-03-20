#include <iostream>
#include <responsejob.h>
#include <stdio.h>
#include <net.h>
#include <requester.h>
#include <queue>
#include <regex.h>
#include <socketpool.h>
using namespace std;
using namespace triple;

Responsejob::Responsejob(Crawler *crawler)
{
    this->crawler = crawler;
}

static string get_host(string url)
{
    int i = 0;
    int len = url.length();
    while (i < len && url[i] != '/' && url[i] != ':')
        i++;
    return string(url, 0, i);
}

//static string get_relative_url(string url)
//{
    //int i = 0;
    //int len = url.length();
    //while (i < len && url[i] != '/')
        //i++;
    //if (i == len)
        //return string("/");
    //return string(url, i, len - i);
//}

static void save_web_page(string url_dup, string web_content)
{
    for (unsigned i = 0; i < url_dup.size(); i++)
        if (url_dup[i] == '/')
            url_dup[i] = '~';
    string page_path = "res/" + url_dup;
    FILE *fp = fopen(page_path.c_str(), "w");
    fprintf(fp, "%s\n", web_content.c_str());
    cout << "save file " + url_dup << endl;
    fclose(fp);
}

static string get_root(string host)
{
    int i = 0;
    while (host[i] != '.')
        i++;
    string root(host, i + 1, host.length() - i - 1);
    return root;
}

deque<string> *Responsejob::get_link(string web_content, string host)
{
    string pattern = "<a.*?href\\s?=\\s?\"(.*?)\".*?>";
    Regex *regex = new Regex(pattern);
    deque<string> *links = regex->match(web_content, 1);
    deque<string> *filt_links = new deque<string>;
    while (links->size())
    {
        string url = links->front();
        links->pop_front();
        if (url.length() == 0)
            continue;
        if (url.find("javascript") == 0)
            continue;
        if (url.find("http://") == 0)
        {
            string clean_url(url, 7, url.length() - 7);
            if (clean_url[clean_url.length() - 1] == '/')
                clean_url.erase(clean_url.length() - 1, 1);
            filt_links->push_back(clean_url);
            continue;
        }
        string full_url = host + "/" + url;
        if (full_url[full_url.length() - 1] == '/')
            full_url.erase(full_url.length() - 1, 1);
        filt_links->push_back(full_url);
    }
    delete(links);
    return filt_links;
}

void Responsejob::assign_site(deque<string> *link)
{
    string aval_root = AVALROOT;
    while (link->size())
    {
        string url = link->front();
        link->pop_front();
        string host = get_host(url);
        string root = get_root(host);
        if (root != aval_root)
            continue;
        Site *site = 0;
        for (unsigned i = 0; i < crawler->get_site_que()->size(); i++)
            if ((*crawler->get_site_que())[i]->get_host() == host)
            {
                site = (*crawler->get_site_que())[i];
                break;
            }
        if (site == 0)
            site = crawler->add_site(host);
        if (site->is_url_exist(url) == 0)
            site->push_being_fetch(url);
    }
}

void Responsejob::run(void *job_data)
{
    Epoll_ptr *ptr = (Epoll_ptr *)job_data;
    string url = ptr->url;
    Net *net = ptr->net;
    Socketpool *socketpool = ptr->socketpool;

    string web_content = net->receive(-1);
    string url_dup = url;
    save_web_page(url_dup, web_content);
    string host = get_host(url);
    deque<string> *filt_link = get_link(web_content, host);
    assign_site(filt_link);
    socketpool->move_to_idle_que(net);
}

#include <resjob.h>
#include <iostream>
#include <stdio.h>
#include <reqthread.h>
#include <net.h>
#include <string>
#include <helper.h>
#include <config.h>
#include <deque>
#include <regex.h>

using namespace std;
using namespace triple;

Resjob::Resjob(Crawler *crawler)
{
    this->crawler = crawler;
}

//保存网页到本地
static void save_page(string url, string content)
{
    replace(&url, '/', '~');
    string save_path = SAVE_DIR + url;
    FILE *fp = fopen(save_path.c_str(), "w");
    if (fp == NULL)
        return;
    fprintf(fp, "%s\n", content.c_str());
    fclose(fp);
    cout << "save file " << url << endl;
}

//得到网页的根域名，以便判断是否抓取
static string get_root(string host)
{
    int i = 0;
    int host_len = host.length();
    while (i < host_len && host[i] != '.')
        i++;
    if (i == host_len)
        return "";
    string root(host, i + 1, host.length() - i - 1);
    return root;
}

//取出网页中的链接
//去掉http://，去掉最后的'/'，去掉javascript
static deque<string> *get_link(string content, string host)
{
    string pattern = "<a.*?href\\s?=\\s?\"(.*?)\".*?>";
    Regex *regex = new Regex(pattern);
    deque<Regex_node *> *links = regex->match(content, 1);
    deque<string> *filt_links = new deque<string>;
    while (links->size())
    {
        Regex_node *rn = links->front();
        links->pop_front();
        string url = rn->content;
        if (url.length() == 0) //空URL，丢弃 
            continue;

        if (url.find("javascript") == 0) //javascript效果，丢弃 
            continue;

        if (url.find("http://") == 0) //保留的URL都是干净的，不要带有http://标记，删除 
        {
            url = ltrim(url, "http://");
            if (url.length() == 0)
                continue;
            url = rtrim(url, "/");
            filt_links->push_back(url);
            continue;
        }
        string full_url = host + "/" + url; //其余的URL都是相对路径，加上host就是绝对路径了 
        full_url = rtrim(full_url, "/");
        filt_links->push_back(full_url);
    }
    delete(links);
    return filt_links;
}

//把URL分配到各个site，去除不抓取的URL
static void assign_site(deque<string> *links, Crawler *crawler)
{
    while (links->size())
    {
        string url = links->front();
        links->pop_front();

        string host = get_host(url);
        string root = get_root(host);
        if (root.length() == 0) //获取root错误，很多URL都是乱七八糟的。。。 
            continue;
        if (root != AVAL_ROOT) //非我要抓取的URL，丢弃 
            continue;

        Site *site = NULL;
        for (unsigned i = 0; i < crawler->get_site_vec()->size(); i++)
            if ((*crawler->get_site_vec())[i]->get_host() == host)
            {
                site = (*crawler->get_site_vec())[i];
                break;
            }
        if (site == NULL)
            site = crawler->add_site(host);
        if (site->is_url_exist(url) == 0)
            site->push_unfetch(url);
    }
}

void Resjob::run(void *data)
{
    Epoll_ptr *ptr = (Epoll_ptr *)data;
    Net *net = ptr->net;
    string url = ptr->url;
    string content = net->receice(); //读取网页内容 
    save_page(url, content); //保存到本地 
    string host = get_host(url);
    deque<string> *links = get_link(content, host);
    assign_site(links, crawler);
    delete(net);
    delete(ptr);
}

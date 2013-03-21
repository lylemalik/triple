#include <helper.h>
using namespace std;

void replace(string *src, char need, char to)
{
    int len = src->length();
    for (int i = 0; i < len; i++)
    {
        if ((*src)[i] == need)
            (*src)[i] = to;
    }
}

string get_host(string url)
{
    int len = url.length();
    int i = 0;
    while (i < len && url[i] != '/' && url[i] != ':')
        i++;
    return string(url, 0, i);
}

string get_relative_url(string url)
{
    int len = url.length();
    int i = 0;
    while (i < len && url[i] != '/')
        i++;
    if (i == len)
        return string("/");
    return string(url, i, len - i);
}

//可以去掉一个字符串
string ltrim(string src, string need)
{
    string test(src, 0, need.length());
    if (test == need)
    {
        string clean(src, need.length(), src.length() - need.length());
        return clean;
    }
    return src;
}

string rtrim(string src, string need)
{
    string test(src, src.length() - need.length(), need.length());
    if (test == need)
    {
        string clean(src, 0, src.length() - need.length());
        return clean;
    }
    return src;
}

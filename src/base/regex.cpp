#include <iostream>
#include <regex.h>
#include <string>
#include <pcre.h>
#include <deque>
using namespace std;
using namespace triple;

Regex::Regex(string pattern)
{
    int erroffset;
    const char *errptr;
    this->re = pcre_compile(pattern.c_str(), 0, &errptr, &erroffset, NULL);
}

string Regex::match_one(string src, int sub_num)
{
    int ovec[OVCOUNT];
    int rc = pcre_exec(re, NULL, src.c_str(), src.length(), 0, 0, ovec, OVCOUNT);
    if (rc < 0)
        return "";
    string match(src, ovec[2 * sub_num], ovec[2 * sub_num + 1] - ovec[2 * sub_num]);
    return match;
}

deque<Regex_node *> *Regex::match(string src, int sub_num)
{
    deque<Regex_node *> *matchque = new deque<Regex_node *>;
    int ovec[OVCOUNT];
    int p = 0;
    int src_len = src.length();
    while (p < src_len)
    {
        int rc = pcre_exec(re, NULL, src.c_str() + p, src_len - p, 0, 0, ovec, OVCOUNT);
        if (rc <= 0)
            return matchque;
        Regex_node *rn = new Regex_node();
        string s(src, p + ovec[2 * sub_num], ovec[2 * sub_num + 1] - ovec[2 * sub_num]);
        rn->content = s;
        rn->start = p + ovec[2 * sub_num];
        rn->end = p + ovec[2 * sub_num + 1];
        matchque->push_back(rn);
        p += ovec[1];
    }
    return matchque;
}

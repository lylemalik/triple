#include <regex.h>
#include <string>
#include <vector>
#include <pcre.h>
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
        return NULL;
    string match(src, ovec[2 * sub_num], ovec[2 * sub_num + 1] - ovec[2 * sub_num]);
    return match;
}

vector<string> *Regex::match(string src, int sub_num)
{
    vector<string> *matchvec = new vector<string>;
    int ovec[OVCOUNT];
    int p = 0;
    int src_len = src.length();
    while (p < src_len)
    {
        int rc = pcre_exec(re, NULL, src.c_str() + p, src_len, 0, 0, ovec, OVCOUNT);
        if (rc < 0)
            return matchvec;
        string s(src, p + ovec[2 * sub_num], ovec[2 * sub_num + 1] - ovec[2 * sub_num]);
        matchvec->push_back(s);
        p += ovec[1];
    }
    return matchvec;
}

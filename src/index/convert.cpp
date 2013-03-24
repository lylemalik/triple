#include <iostream>
#include <stdlib.h>
#include <convert.h>
#include <errno.h>
using namespace std;
using namespace triple;

Convert::Convert(string src_charset, string to_charset)
{
    this->src_charset = src_charset;
    this->to_charset = to_charset;
    cd = iconv_open((char *)to_charset.c_str(), (char *)src_charset.c_str());
}

int Convert::real_exec(char *src, char *to, size_t src_len, size_t to_len)
{
    if (iconv(cd, &src, &src_len, &to, &to_len) == (size_t)-1)
        return -1;
    return 1;
}

string Convert::exec(string src)
{
    char *src_char = (char *)src.c_str();
    size_t src_len = src.length();
    size_t to_len = src_len * 2;
    char *to = (char *)calloc(to_len, sizeof(char));
    if (real_exec(src_char, to, src_len, to_len) == -1)
        return "";
    return string(to);
}

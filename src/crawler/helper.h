#ifndef __HELPER_H__
#define __HELPER_H__

#include <string>
using namespace std;

void replace(string *src, char need, char to);
string get_host(string url);
string get_relative_url(string url);
string ltrim(string src, string need);
string rtrim(string src, string need);
#endif

#ifndef __REGEX_H__
#define __REGEX_H__

#include <string>
#include <pcre.h>
#include <deque>
using namespace std;

#define OVCOUNT 30
namespace triple
{
    class Regex
    {
        private:
            pcre *re;
        public:
            Regex() {};
            Regex(string pattern);
            ~Regex() {pcre_free(re);}
            string match_one(string src, int sub_num);
            deque<string> *match(string src, int sub_num);
    };
}
#endif

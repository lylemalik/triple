#ifndef __REGEX_H__
#define __REGEX_H__

#include <string>
#include <pcre.h>
#include <deque>
using namespace std;

#define OVCOUNT 30
namespace triple
{
    class Regex_node
    {
        public:
            int start;
            int end;
            string content;
    };
    class Regex
    {
        private:
            pcre *re;
        public:
            Regex() {};
            Regex(string pattern);
            ~Regex() {pcre_free(re);}
            string match_one(string src, int sub_num);
            deque<Regex_node *> *match(string src, int sub_num);
    };
}
#endif

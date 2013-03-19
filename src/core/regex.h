#ifndef __REGEX_H__
#define __REGEX_H__
#include <string>
#include <vector>
#include <pcre.h>
#include <queue>
using namespace std;

#define OVCOUNT 30
namespace triple
{
    class Regex
    {
        private:
            pcre *re;
        public:
            Regex()
            {
                re = 0;
            }
            Regex(string pattern);
            string match_one(string src, int sub_num);
            deque<string> *match(string src, int sub_num);
            ~Regex()
            {
                pcre_free(re);
            }
    };
}
#endif

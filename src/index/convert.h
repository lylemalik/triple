#ifndef __CONVERT_H__
#define __CONVERT_H__

#include <config.h>
#include <string>
#include <iconv.h>

using namespace std;
namespace triple
{
    class Convert
    {
        private:
            string src_charset;
            string to_charset;
            iconv_t cd;
            int real_exec(char *src, char *to, size_t src_len, size_t to_len);
        public:
            Convert() {};
            Convert(string src_charset, string to_charset);
            string exec(string src);
    };
}

#endif

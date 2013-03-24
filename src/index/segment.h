#ifndef __SEGMENT_H__
#define __SEGMENT_H__

#include <scws.h>
#include <deque>
#include <string>
#include <config.h>
using namespace std;
namespace triple
{
    class Segment
    {
        private:
            scws_t s;
            Segment()
            {
                s = scws_new();
                scws_set_charset(s, "utf8");
                scws_set_dict(s, XDB_PATH, SCWS_XDICT_XDB);
                scws_set_rule(s, INI_PATH);
                scws_set_ignore(s, 1);
            }
            static Segment *seg;
        public:
            static Segment *get_seg()
            {
                if (seg == NULL)
                    seg = new Segment();
                return seg;
            }
            deque<string> *exec(string src);
    };
}

#endif

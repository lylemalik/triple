#include <segment.h>
using namespace std;
using namespace triple;

deque<string> *Segment::exec(string src)
{
    scws_send_text(s, src.c_str(), src.length());
    scws_res_t result;
    deque<string> *seg_que = new deque<string>;
    while ((result = scws_get_result(s)))
    {
        while (result)
        {
            string s(src, result->off, result->len);
            seg_que->push_back(s);
            result = result->next;
        }
    }
    scws_free_result(result);
    return seg_que;
}

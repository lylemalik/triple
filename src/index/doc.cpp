#include <doc.h>
#include <iostream>
#include <fstream>
#include <regex.h>
#include <convert.h>
#include <segment.h>

using namespace std;
using namespace triple;

Doc::Doc(string name)
{
    in.open(name.c_str(), ios::in);
    string buf;
    while (getline(in, buf))
        content += buf + '\n';
}

Doc::~Doc()
{
    in.close();
}

//编码问题，如果是gbk,则转成utf8
string Doc::charset_convert()
{
    string pattern = "charset\\s?=\\s?(.*?)\"";
    Regex *regex = new Regex(pattern);
    string charset = regex->match_one(content, 1);
    if (charset == "utf-8" || charset == "utf8") //如果文档是utf8编码，则不做特别处理 
        return content;
    else if (charset == "gbk" || charset == "gb2312") //如果是gbk编码，则转换成utf8编码 
    {
        Convert *con = new Convert("gbk", "utf8");
        return con->exec(content);
    }
    else //其他编码不予以考虑，直接跳过 
        return "";
}

//过滤网页，去掉javascript,css,注释等东西
void Doc::filter()
{
    unsigned found1 = content.find("<html");
    unsigned found2 = content.find("<HTML");
    unsigned found = (found1 > found2 ? found2 : found1);
    string content_temp(content, found, content.length() - found);
    content = content_temp;

    string pattern[3] = {"<script[\\s\\S]*?</script>", 
        "<style[\\s\\S]*?</style>", 
        "<!--[\\s\\S]*?-->"};
    for (int i = 0; i < 3; i++)
    {
        Regex *regex = new Regex(pattern[i]);
        deque<Regex_node *> *regque = regex->match(content, 0);
        while (regque->size())
        {
            Regex_node *rn = regque->front();
            regque->pop_front();
            for (int j = rn->start; j <= rn->end; j++)
                content[j] = ' ';
        }
    }
}

//TODO:把文档内容分析过滤，去掉标签和js，这个分析很简单，不能做到
//完整和正确的分析，需要改善
int Doc::parse()
{
    this->content = charset_convert();
    if (content == "")
        return -1;
    filter(); //过滤文档; 
    int pos = 0, pos_mark = 0;
    while (content[pos])
    {
        if (content[pos] == '<')
            pos_mark = pos;
        else if (content[pos] == '>')
            for (int i = pos_mark; i <= pos; i++)
                content[i] = ' ';
        pos++;
    }
    return 1;
}

deque<string> *Doc::segment()
{
    Segment *seg = Segment::get_seg();
    deque<string> *segque = seg->exec(content);
    return segque;
}

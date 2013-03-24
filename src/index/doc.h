#ifndef __DOC_H__
#define __DOC_H__

#include <string>
#include <deque>
#include <fstream>
using namespace std;
namespace triple
{
    class Doc
    {
        private:
            string content;
            ifstream in;
            string charset_convert();
            void filter();
        public:
            Doc() {};
            Doc(string name);
            ~Doc();
            int parse();
            deque<string> *segment();
            string get_content() {return content;}
    };
}

#endif

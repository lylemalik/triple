#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <index.h>
#include <segment.h>
#include <convert.h>
#include <deque>
#include <convert.h>
#include <doc.h>
#include <dirent.h>
#include <sys/types.h>
#include <config.h>
#include <time.h>
using namespace std;
using namespace triple;

void Index::start()
{
    DIR *dir;
    struct dirent *d;
    dir = opendir(SAVE_DIR);
    string save_dir = SAVE_DIR;
    clock_t start, end;
    double duration;
    start = clock();
    while ((d = readdir(dir)))
    {
        if (d->d_name[0] == '.')
            continue;
        string doc_path = save_dir + d->d_name;
        Doc *doc = new Doc(doc_path);
        if (doc->parse() == -1)
            continue;
        deque<string> *segque = doc->segment();
    }
    end = clock();
    duration = (double)(end - start) / CLOCKS_PER_SEC;
    cout << duration << endl;
}

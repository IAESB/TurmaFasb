#ifndef OPTIONSARGS
#define OPTIONSARGS

#include <vector>
#include <string>
using namespace std;

struct OptionsArgs
{
    int port = 5678;
    string webDir = "../www";
    string database;
    string mentor;
};

#endif // OPTIONSARGS


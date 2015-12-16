#ifndef OPTIONSARGS
#define OPTIONSARGS

#include <vector>
#include <string>
using namespace std;

struct OptionsArgs
{
    int port = 5678;
    int ano = 0;
    int semestre = 0;
    bool sync = false;
    string webDir = "../www";
    string database;
    string mentor;
};

#endif // OPTIONSARGS


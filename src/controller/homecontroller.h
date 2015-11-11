#ifndef HOMECONTROLLER_H
#define HOMECONTROLLER_H

#include "controllerbase.h"
using namespace Mongoose;

class HomeController : public ControllerBase
{
public:
    HomeController();
    ~HomeController();
    void home(Request &request, StreamResponse &response);
    void appcache(Request &request, StreamResponse &response);
    void setup();
};

#endif // HOMECONTROLLER_H

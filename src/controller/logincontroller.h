#ifndef LOGINCONTROLLER_H
#define LOGINCONTROLLER_H

#include "model/loginmodel.h"
#include "controllerbase.h"

class LoginController : public ControllerBase
{
    LoginModel model;
public:
    LoginController();
    ~LoginController();
    void login(Request &request, StreamResponse &response);
    void status(Request &request, StreamResponse &response);
    void setup();
};

#endif // LOGINCONTROLLER_H

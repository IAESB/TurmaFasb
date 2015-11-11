#ifndef SHAREDGALLERY_H
#define SHAREDGALLERY_H

#include <mongoose/Server.h>
#include "optionsargs.h"
#include "controller/homecontroller.h"
#include "controller/logincontroller.h"
#include "controller/materiacontroller.h"

using namespace Mongoose;

class ServerManager
{
    OptionsArgs options;
    Server server;
    Model model;
    HomeController home;
    LoginController login;
    MateriaController materia;

public:
    ServerManager(OptionsArgs& options);
    virtual ~ServerManager();
    void start();
    void stop();
};

#endif // SHAREDGALLERY_H

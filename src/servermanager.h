#ifndef SHAREDGALLERY_H
#define SHAREDGALLERY_H

#include <mongoose/Server.h>
#include "optionsargs.h"
#include "basesync.h"
#include "controller/homecontroller.h"
#include "controller/logincontroller.h"
#include "controller/materiacontroller.h"
#include "controller/recadocontroller.h"
#include "controller/arquivocontroller.h"

using namespace Mongoose;

class ServerManager
{
    OptionsArgs options;
    Server server;
    Model model;
    HomeController home;
    LoginController login;
    MateriaController materia;
    RecadoController recado;
    ArquivoController arquivo;
    bool processando;

public:
    ServerManager(OptionsArgs& options);
    virtual ~ServerManager();
    void start();
    void stop();
    bool isProcessando() const;
    void setProcessando(bool value);
};

#endif // SHAREDGALLERY_H

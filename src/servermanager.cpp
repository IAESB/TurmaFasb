#include "servermanager.h"

ServerManager::ServerManager(OptionsArgs& options)
{
    this->options = options;
    model.openRepository(options.database);
    server.setOption("listening_port", to_string(options.port) );
    server.setOption("document_root", options.webDir);
    server.registerController(&home);
    server.registerController(&login);
    server.registerController(&materia);
}

ServerManager::~ServerManager()
{
}

void ServerManager::start()
{
    server.start();
}

void ServerManager::stop()
{
    server.start();
}


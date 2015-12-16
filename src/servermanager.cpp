#include "servermanager.h"
#include <thread>


bool ServerManager::isProcessando() const
{
    return processando;
}

void ServerManager::setProcessando(bool value)
{
    processando = value;
}
ServerManager::ServerManager(OptionsArgs& options)
{
    this->options = options;
    model.openRepository(options.database);
    arquivo.setDirStorage(options.webDir+"/filestorage/");
	server.setOption("listening_port", to_string(options.port));
	server.setOption("document_root", options.webDir);
	server.setOption("enable_directory_listing", "yes");	
    server.registerController(&home);
    server.registerController(&login);
    server.registerController(&materia);
    server.registerController(&recado);
    server.registerController(&arquivo);
}

ServerManager::~ServerManager()
{
}

void ServerManager::start()
{
    processando=true;
    if(options.sync)
    {
        BaseSync baseSync(options);
        baseSync.init();
        processando=false;
    }
    else
    {
        server.start();
    }
}

void ServerManager::stop()
{
    if( ! options.sync)
        server.stop();

    processando=false;
}


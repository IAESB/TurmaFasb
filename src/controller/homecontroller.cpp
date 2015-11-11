#include "homecontroller.h"
#include "mongoose/Server.h"
#include <fstream>

HomeController::HomeController()
{
}

HomeController::~HomeController()
{

}

void HomeController::home(Request &request, StreamResponse &response)
{
    response.setHeader("Access-Control-Allow-Origin", "*");
    ifstream file;
    if(getSession(request, response).hasValue("usuario")){
        file.open(server->getOption("document_root")+"/index.html");
    }else{
        file.open(server->getOption("document_root")+"/login.html");
    }
    response << file.rdbuf();
}

void HomeController::appcache(Request &request, StreamResponse &response)
{
    response.setHeader("Content-Type:", "text/cache-manifest");
    ifstream file(server->getOption("document_root")+"/manifest.appcache");
    response << file.rdbuf();
}


void HomeController::setup()
{
    addRoute("GET", "/", HomeController, home);
    addRoute("GET", "/manifest.appcache", HomeController, appcache);
}


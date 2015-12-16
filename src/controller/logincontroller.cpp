#include "logincontroller.h"
#include <json/json.h>

LoginController::LoginController(){}

LoginController::~LoginController(){}

void LoginController::setup()
{
    addRoute("POST", "/login", LoginController, login);
    addRoute("GET", "/login/status", LoginController, status);
}

void LoginController::login(Request &request, StreamResponse &response)
{
    Json::Value value;
    value["operation"] = "login";
    UsuarioPtr usuario = model.login(request.get("login"), request.get("senha"));
    if(usuario){
        getSession(request, response).setValue("usuario", usuario);
        value["usuario"]["id"] = usuario->getId();
        value["usuario"]["nome"] = usuario->getNome();
        value["usuario"]["foto"] = usuario->getFoto();
        value["usuario"]["login"] = usuario->getLogin();
        value["usuario"]["senha"] = usuario->getSenha();
        value["success"] = true;
    }
    else{
        value["success"] = false;
    }
    response << value;
}

void LoginController::status(Request &request, StreamResponse &response)
{
    Json::Value value;
    value["operation"] = "status";
    UsuarioPtr usuario = getSession(request, response).get<UsuarioPtr>("usuario");
    if(usuario){
        value["logged"] = true;
        value["usuario_id"] = usuario->getId();
    }else
        value["logged"] = false;

    response << value;
}


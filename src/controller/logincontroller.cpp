#include "logincontroller.h"
#include <jsoncpp/json/json.h>

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
    UsuarioPtr usuario = model.login(request.get("email"), request.get("senha"));
    if(usuario){
        getSession(request, response).setValue("usuario", usuario);
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


#include "recadocontroller.h"

RecadoController::RecadoController()
{

}

void RecadoController::save(Request &request, StreamResponse &response)
{
    Json::Value result;
    result["operation"] = "recado_save";
    UsuarioPtr usuario = getSession(request, response).get<UsuarioPtr>("usuario");
    if(usuario){
        int idNovoRecado=0;
        RecadoPtr recado = request2recado(request);
        const string& materia_id = request.get("materia_id");
        const string& destinatario_id = request.get("destinatario_id");
        if( ! materia_id.empty() ){
            MateriaPtr materia(new Materia(stoi(materia_id)));
            idNovoRecado = model.save(recado, usuario, materia);
        }
        else if( ! destinatario_id.empty() ){
            UsuarioPtr destinatario(new Usuario(stoi(destinatario_id)));
            //idNovoRecado = model.save(recado, usuario, destinatario);
        }
        if(idNovoRecado){
            result["data"] = to_string(recado->getData());
            result["success"] = true;
        }
        else
            result["success"] = false;
    }else{
        result["success"] = false;
        result["erro_msg"] = "Não permitido";
    }

    response << result;
}

void RecadoController::list(Request &request, StreamResponse &response)
{
    Json::Value item;
    Json::Value result;
    result["operation"] = "recado_list";
    UsuarioPtr usuario = getSession(request, response).get<UsuarioPtr>("usuario");
    if(usuario){
        const string& materia_id = request.get("materia_id");
        auto list = model.list(materia_id);
        for(RecadoHasMateriaPtr rm: list){
            item["texto"] = rm->getRecado()->getTexto();
            item["data"] = to_string(rm->getRecado()->getData());
            item["remetente"] = rm->getUsuario()->getNome();
            result["recados"].append(item);
        }
        result["success"] = true;
    }else{
        result["success"] = false;
        result["erro_msg"] = "Não permitido";
    }

    response << result;
}

RecadoController::~RecadoController()
{

}

void RecadoController::setup()
{
    addRoute("POST", "/recado/save", RecadoController, save);
    addRoute("GET", "/recado/list", RecadoController, list);
}

RecadoPtr RecadoController::request2recado(Request &request)
{
    time_t now = time(NULL);
    RecadoPtr recado(new Recado(0));
    recado->setTexto(request.get("texto"));
    recado->setData(*localtime(&now));

    return recado;
}


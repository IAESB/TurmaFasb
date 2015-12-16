#include "materiacontroller.h"
#include <boost/lexical_cast.hpp>
#include <json/json.h>

MateriaController::MateriaController()
{
}

void MateriaController::setup()
{
    addRoute("GET", "/materia/list", MateriaController, list);
    addRoute("GET", "/materia/list_medias", MateriaController, listMedias);
    addRoute("GET", "/materia/notas", MateriaController, notas);
	addRoute("GET", "/materia/add", MateriaController, add);
	addRoute("GET", "/materia/show", MateriaController, show);
	addRoute("GET", "/materia/edit", MateriaController, edit);
    addRoute("POST", "/materia/update", MateriaController, update);
	addRoute("POST", "/materia/save", MateriaController, save);
	addRoute("POST", "/materia/remove", MateriaController, remove);
}
void MateriaController::list(Request &request, StreamResponse &response)
{
    //response.setHeader("Content-type", "text/json; charset=utf-8");
    Json::Value result;
    Json::Value arrayMateria;
    result["operation"] = "materia_list";
    UsuarioPtr usuario = getSession(request, response).get<UsuarioPtr>("usuario");
    if(usuario){
        MateriaHasUsuarioList list = model.list(usuario);
        for(MateriaHasUsuarioPtr materiaUsuario: list)
            arrayMateria.append(materia2Json(materiaUsuario->getMateria()));
        result["materias"] = arrayMateria;
        result["success"] = true;
    }else{
        result["success"] = false;
    }

    response << result;
}

void MateriaController::listMedias(Request &request, StreamResponse &response)
{
    Json::Value result;
    Json::Value materia;
    result["operation"] = "materia_list_medias";
    UsuarioPtr usuario = getSession(request, response).get<UsuarioPtr>("usuario");
    if(usuario){
        NotaList medias = model.medias(usuario);
        for(int i=0; i<medias.size(); i+=2)
        {
            materia["nome"] = medias[i]->getMateria()->getNome();
            materia["aluno"] = medias[i]->getValor();
            materia["turma"] = medias[i+1]->getValor();
            result["medias"].append(materia);
        }
        result["success"] = true;
    }else{
        result["success"] = false;
    }

    response << result;
}

void MateriaController::notas(Request &request, StreamResponse &response)
{
    Json::Value result;
    result["operation"] = "materia_notas";
    UsuarioPtr usuario = getSession(request, response).get<UsuarioPtr>("usuario");
    if(usuario){
        string materia_id = request.get("materia_id", "");
        NotaList notas = model.notas(materia_id, usuario);
        Json::Value value;
        for(NotaPtr& nota: notas)
        {
            value["valor"] = nota->getValor();
            value["descricao"] = nota->getDescricao();
            result["notas"].append(value);
        }
        notas = model.medias(materia_id);
        for(NotaPtr& nota: notas)
        {
            value["valor"] = nota->getValor();
            value["descricao"] = nota->getDescricao();
            result["medias"].append(value);
        }
        result["success"] = true;
    }else{
        result["success"] = false;
    }

    response << result;
}


#include <boost/locale.hpp>
#include <locale>

Json::Value MateriaController::materia2Json(const MateriaPtr& materia)
{
    Json::Value value;
    value["id"] = materia->getId();
    value["nome"] = boost::locale::conv::to_utf<char>(materia->getNome(),"Latin1");
    value["descricao"] = materia->getDescricao();
    value["usuario"] = materia->getUsuario()->getId();

    return value;
}

void MateriaController::add(Request &request, StreamResponse &response)
{
}
void MateriaController::show(Request &request, StreamResponse &response)
{
}
void MateriaController::save(Request &request, StreamResponse &response)
{
	Materia obj = request2Materia(request);
	model.save(obj);
	redirecionar(response, "/materia/list");
}
void MateriaController::edit(Request &request, StreamResponse &response)
{
}
void MateriaController::update(Request &request, StreamResponse &response)
{
	Materia obj = request2Materia(request);
	MateriaPtr oldObj = model.get(obj);
	if(!oldObj)
		throw runtime_error("Not Exist");
	model.update(*oldObj, obj);
	redirecionar(response, "/materia/list");
}
void MateriaController::remove(Request &request, StreamResponse &response)
{
	Materia obj = request2Materia(request);
	model.remove(obj);
	redirecionar(response, "/materia/list");
}
Materia MateriaController::request2Materia(Request &request)
{
	Materia obj;
	obj.setId( boost::lexical_cast<int>( request.get("id", "0")) );
	obj.setNome( request.get("nome") );
	obj.setCodigo( request.get("codigo") );
    obj.setDescricao( request.get("descricao") );
    return obj;
}


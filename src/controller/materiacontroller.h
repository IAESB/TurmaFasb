#ifndef MATERIACONTROLLER_H
#define MATERIACONTROLLER_H

#include "controllerbase.h"
#include "model/materiamodel.h"
#include <jsoncpp/json/json.h>

class MateriaController : public ControllerBase
{
	MateriaModel model;
public:
	MateriaController();
	void setup();
	void list(Request &request, StreamResponse &response);
	void add(Request &request, StreamResponse &response);
	void save(Request &request, StreamResponse &response);
	void edit(Request &request, StreamResponse &response);
	void update(Request &request, StreamResponse &response);
	void show(Request &request, StreamResponse &response);
	void remove(Request &request, StreamResponse &response);
	Materia request2Materia(Request& request);
    Json::Value materia2Json(const MateriaPtr& materia);
};

#endif

#ifndef MATERIAMODEL_H
#define MATERIAMODEL_H

#include "model.h"
class MateriaModel : public Model
{
public:
	int save(Materia& materia);
	void update(Materia& materia);
	void update(Materia& oldObj, Materia& newObj);
	void remove(Materia& materia);
    MateriaPtr get(const Materia& materia);
    MateriaList list(const string& where="");
    MateriaHasUsuarioList list(const UsuarioPtr& usuario);
};
#endif

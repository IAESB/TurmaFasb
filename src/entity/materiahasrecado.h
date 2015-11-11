#ifndef MATERIAHASRECADO_H
#define MATERIAHASRECADO_H

#include <iostream>
#include <memory>
#include <vector>
#include "materia.h"
#include "recado.h"
#include "usuario.h"

using namespace std;

class MateriaHasRecado;
typedef shared_ptr<MateriaHasRecado> MateriaHasRecadoPtr;
typedef vector<MateriaHasRecadoPtr> MateriaHasRecadoList;

class MateriaHasRecado
{
	MateriaPtr materia; //key: PRI
	RecadoPtr recado; //key: PRI
	UsuarioPtr usuario; //key: PRI
public:
	MateriaHasRecado();
	MateriaHasRecado(MateriaPtr materia, RecadoPtr recado, UsuarioPtr usuario);
	void init();
	MateriaPtr getMateria() const;
	void setMateria(MateriaPtr value);
	RecadoPtr getRecado() const;
	void setRecado(RecadoPtr value);
	UsuarioPtr getUsuario() const;
	void setUsuario(UsuarioPtr value);
};



#endif // MATERIAHASRECADO_H

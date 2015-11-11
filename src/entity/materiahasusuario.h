#ifndef MATERIAHASUSUARIO_H
#define MATERIAHASUSUARIO_H

#include <iostream>
#include <memory>
#include <vector>
#include "materia.h"
#include "usuario.h"

using namespace std;

class MateriaHasUsuario;
typedef shared_ptr<MateriaHasUsuario> MateriaHasUsuarioPtr;
typedef vector<MateriaHasUsuarioPtr> MateriaHasUsuarioList;

class MateriaHasUsuario
{
	MateriaPtr materia; //key: PRI
	UsuarioPtr usuario; //key: PRI
public:
	MateriaHasUsuario();
	MateriaHasUsuario(MateriaPtr materia, UsuarioPtr usuario);
	void init();
	MateriaPtr getMateria() const;
	void setMateria(MateriaPtr value);
	UsuarioPtr getUsuario() const;
	void setUsuario(UsuarioPtr value);
};



#endif // MATERIAHASUSUARIO_H

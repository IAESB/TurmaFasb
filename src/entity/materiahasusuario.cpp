#include "materiahasusuario.h"

MateriaHasUsuario::MateriaHasUsuario(){
	init();
}
MateriaHasUsuario::MateriaHasUsuario(MateriaPtr materia, UsuarioPtr usuario)
{
	init();
	this->materia = materia;
	this->usuario = usuario;
}

void MateriaHasUsuario::init()
{
}
MateriaPtr MateriaHasUsuario::getMateria() const
{
	return materia;
}
void MateriaHasUsuario::setMateria(MateriaPtr value)
{
	materia = value;
}
UsuarioPtr MateriaHasUsuario::getUsuario() const
{
	return usuario;
}
void MateriaHasUsuario::setUsuario(UsuarioPtr value)
{
	usuario = value;
}


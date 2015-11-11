#include "materiahasrecado.h"

MateriaHasRecado::MateriaHasRecado(){
	init();
}
MateriaHasRecado::MateriaHasRecado(MateriaPtr materia, RecadoPtr recado, UsuarioPtr usuario)
{
	init();
	this->materia = materia;
	this->recado = recado;
	this->usuario = usuario;
}

void MateriaHasRecado::init()
{
}
MateriaPtr MateriaHasRecado::getMateria() const
{
	return materia;
}
void MateriaHasRecado::setMateria(MateriaPtr value)
{
	materia = value;
}
RecadoPtr MateriaHasRecado::getRecado() const
{
	return recado;
}
void MateriaHasRecado::setRecado(RecadoPtr value)
{
	recado = value;
}
UsuarioPtr MateriaHasRecado::getUsuario() const
{
	return usuario;
}
void MateriaHasRecado::setUsuario(UsuarioPtr value)
{
	usuario = value;
}


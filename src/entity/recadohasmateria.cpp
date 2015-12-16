#include "recadohasmateria.h"

RecadoHasMateria::RecadoHasMateria(){
	init();
}
RecadoHasMateria::RecadoHasMateria(MateriaPtr materia, RecadoPtr recado, UsuarioPtr usuario)
{
	init();
	this->materia = materia;
	this->recado = recado;
	this->usuario = usuario;
}

void RecadoHasMateria::init()
{
}
MateriaPtr RecadoHasMateria::getMateria() const
{
	return materia;
}
void RecadoHasMateria::setMateria(MateriaPtr value)
{
	materia = value;
}
RecadoPtr RecadoHasMateria::getRecado() const
{
	return recado;
}
void RecadoHasMateria::setRecado(RecadoPtr value)
{
	recado = value;
}
UsuarioPtr RecadoHasMateria::getUsuario() const
{
	return usuario;
}
void RecadoHasMateria::setUsuario(UsuarioPtr value)
{
	usuario = value;
}


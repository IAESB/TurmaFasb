#include "arquivo.h"

Arquivo::Arquivo(){
	init();
}
Arquivo::Arquivo(int id)
{
	init();
	this->id = id;
}

void Arquivo::init()
{
	data = {0};
}
int Arquivo::getId() const
{
	return id;
}
void Arquivo::setId(int value)
{
	id = value;
}
std::string Arquivo::getPath() const
{
	return path;
}
void Arquivo::setPath(std::string value)
{
	path = value;
}
tm Arquivo::getData() const
{
	return data;
}
void Arquivo::setData(tm value)
{
	data = value;
}
MateriaPtr Arquivo::getMateria() const
{
	return materia;
}
void Arquivo::setMateria(MateriaPtr value)
{
	materia = value;
}
UsuarioPtr Arquivo::getUsuario() const
{
	return usuario;
}
void Arquivo::setUsuario(UsuarioPtr value)
{
	usuario = value;
}


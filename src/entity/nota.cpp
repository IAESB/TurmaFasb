#include "nota.h"

Nota::Nota(){
	init();
}
Nota::Nota(int id)
{
	init();
	this->id = id;
}

void Nota::init()
{
}
int Nota::getId() const
{
	return id;
}
void Nota::setId(int value)
{
	id = value;
}
MateriaPtr Nota::getMateria() const
{
	return materia;
}
void Nota::setMateria(MateriaPtr value)
{
	materia = value;
}
UsuarioPtr Nota::getUsuario() const
{
	return usuario;
}
void Nota::setUsuario(UsuarioPtr value)
{
	usuario = value;
}
double Nota::getValor() const
{
	return valor;
}
void Nota::setValor(double value)
{
	valor = value;
}
std::string Nota::getDescricao() const
{
	return descricao;
}
void Nota::setDescricao(std::string value)
{
	descricao = value;
}


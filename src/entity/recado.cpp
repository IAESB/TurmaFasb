#include "recado.h"

Recado::Recado(){
	init();
}
Recado::Recado(int id)
{
	init();
	this->id = id;
}

void Recado::init()
{
	data = {0};
}
int Recado::getId() const
{
	return id;
}
void Recado::setId(int value)
{
	id = value;
}
std::string Recado::getTexto() const
{
	return texto;
}
void Recado::setTexto(std::string value)
{
	texto = value;
}
tm Recado::getData() const
{
	return data;
}
void Recado::setData(tm value)
{
	data = value;
}
RecadoPtr Recado::getRecado() const
{
	return recado;
}
void Recado::setRecado(RecadoPtr value)
{
	recado = value;
}


#include "usuario.h"

Usuario::Usuario(){
	init();
}
Usuario::Usuario(int id)
{
	init();
	this->id = id;
}

void Usuario::init()
{
}
int Usuario::getId() const
{
	return id;
}
void Usuario::setId(int value)
{
	id = value;
}
std::string Usuario::getNome() const
{
	return nome;
}
void Usuario::setNome(std::string value)
{
	nome = value;
}
std::string Usuario::getLogin() const
{
	return login;
}
void Usuario::setLogin(std::string value)
{
	login = value;
}
std::string Usuario::getSenha() const
{
	return senha;
}
void Usuario::setSenha(std::string value)
{
	senha = value;
}
std::string Usuario::getMatricula() const
{
	return matricula;
}
void Usuario::setMatricula(std::string value)
{
	matricula = value;
}
std::string Usuario::getFoto() const
{
	return foto;
}
void Usuario::setFoto(std::string value)
{
	foto = value;
}


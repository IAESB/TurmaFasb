#include "materia.h"

Materia::Materia(){
	init();
}
Materia::Materia(int id)
{
	init();
	this->id = id;
}

void Materia::init()
{
}
int Materia::getId() const
{
	return id;
}
void Materia::setId(int value)
{
	id = value;
}
std::string Materia::getNome() const
{
	return nome;
}
void Materia::setNome(std::string value)
{
	nome = value;
}
std::string Materia::getCodigo() const
{
	return codigo;
}
void Materia::setCodigo(std::string value)
{
	codigo = value;
}
std::string Materia::getDescricao() const
{
	return descricao;
}
void Materia::setDescricao(std::string value)
{
	descricao = value;
}
int Materia::getAno() const
{
	return ano;
}
void Materia::setAno(int value)
{
	ano = value;
}
int Materia::getSemestre() const
{
	return semestre;
}
void Materia::setSemestre(int value)
{
	semestre = value;
}
std::string Materia::getCurso() const
{
	return curso;
}
void Materia::setCurso(std::string value)
{
	curso = value;
}
UsuarioPtr Materia::getUsuario() const
{
	return usuario;
}
void Materia::setUsuario(UsuarioPtr value)
{
	usuario = value;
}


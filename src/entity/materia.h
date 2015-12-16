#ifndef MATERIA_H
#define MATERIA_H

#include <iostream>
#include <memory>
#include <vector>
#include "usuario.h"

using namespace std;

class Materia;
typedef shared_ptr<Materia> MateriaPtr;
typedef vector<MateriaPtr> MateriaList;

class Materia
{
	int id; //key: PRI
	std::string nome;
	std::string codigo;
	std::string descricao;
	int ano;
	int semestre;
	std::string curso;
	UsuarioPtr usuario; //key: MUL
public:
	Materia();
	Materia(int id);
	void init();
	int getId() const;
	void setId(int value);
	std::string getNome() const;
	void setNome(std::string value);
	std::string getCodigo() const;
	void setCodigo(std::string value);
	std::string getDescricao() const;
	void setDescricao(std::string value);
	int getAno() const;
	void setAno(int value);
	int getSemestre() const;
	void setSemestre(int value);
	std::string getCurso() const;
	void setCurso(std::string value);
	UsuarioPtr getUsuario() const;
	void setUsuario(UsuarioPtr value);
};



#endif // MATERIA_H

#ifndef NOTA_H
#define NOTA_H

#include <iostream>
#include <memory>
#include <vector>
#include "materia.h"
#include "usuario.h"

using namespace std;

class Nota;
typedef shared_ptr<Nota> NotaPtr;
typedef vector<NotaPtr> NotaList;

class Nota
{
	int id; //key: PRI
	MateriaPtr materia; //key: PRI
	UsuarioPtr usuario; //key: PRI
	double valor;
	std::string descicao;
public:
	Nota();
	Nota(int id, MateriaPtr materia, UsuarioPtr usuario);
	void init();
	int getId() const;
	void setId(int value);
	MateriaPtr getMateria() const;
	void setMateria(MateriaPtr value);
	UsuarioPtr getUsuario() const;
	void setUsuario(UsuarioPtr value);
	double getValor() const;
	void setValor(double value);
	std::string getDescicao() const;
	void setDescicao(std::string value);
};



#endif // NOTA_H

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
	MateriaPtr materia; //key: MUL
	UsuarioPtr usuario; //key: MUL
	double valor;
	std::string descricao;
public:
	Nota();
	Nota(int id);
	void init();
	int getId() const;
	void setId(int value);
	MateriaPtr getMateria() const;
	void setMateria(MateriaPtr value);
	UsuarioPtr getUsuario() const;
	void setUsuario(UsuarioPtr value);
	double getValor() const;
	void setValor(double value);
	std::string getDescricao() const;
	void setDescricao(std::string value);
};



#endif // NOTA_H

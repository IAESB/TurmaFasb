#ifndef ARQUIVO_H
#define ARQUIVO_H

#include <iostream>
#include <memory>
#include <vector>
#include "materia.h"
#include "usuario.h"

using namespace std;

class Arquivo;
typedef shared_ptr<Arquivo> ArquivoPtr;
typedef vector<ArquivoPtr> ArquivoList;

class Arquivo
{
	int id; //key: PRI
	std::string path;
	tm data;
	MateriaPtr materia; //key: MUL
	UsuarioPtr usuario; //key: MUL
public:
	Arquivo();
	Arquivo(int id);
	void init();
	int getId() const;
	void setId(int value);
	std::string getPath() const;
	void setPath(std::string value);
	tm getData() const;
	void setData(tm value);
	MateriaPtr getMateria() const;
	void setMateria(MateriaPtr value);
	UsuarioPtr getUsuario() const;
	void setUsuario(UsuarioPtr value);
};



#endif // ARQUIVO_H

#ifndef RECADOHASMATERIA_H
#define RECADOHASMATERIA_H

#include <iostream>
#include <memory>
#include <vector>
#include "materia.h"
#include "recado.h"
#include "usuario.h"

using namespace std;

class RecadoHasMateria;
typedef shared_ptr<RecadoHasMateria> RecadoHasMateriaPtr;
typedef vector<RecadoHasMateriaPtr> RecadoHasMateriaList;

class RecadoHasMateria
{
	MateriaPtr materia; //key: PRI
	RecadoPtr recado; //key: PRI
	UsuarioPtr usuario; //key: PRI
public:
	RecadoHasMateria();
	RecadoHasMateria(MateriaPtr materia, RecadoPtr recado, UsuarioPtr usuario);
	void init();
	MateriaPtr getMateria() const;
	void setMateria(MateriaPtr value);
	RecadoPtr getRecado() const;
	void setRecado(RecadoPtr value);
	UsuarioPtr getUsuario() const;
	void setUsuario(UsuarioPtr value);
};



#endif // RECADOHASMATERIA_H

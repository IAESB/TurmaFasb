#ifndef REPOSITORY_H
#define REPOSITORY_H
#include <soci/soci.h>
#include <typeinfo>
#include "materiarepository.h"
#include "materiahasrecadorepository.h"
#include "materiahasusuariorepository.h"
#include "notarepository.h"
#include "recadorepository.h"
#include "recadohasusuariorepository.h"
#include "usuariorepository.h"

class Repository
{
	soci::session dataBase;
	MateriaRepository materia;
	MateriaHasRecadoRepository materiahasrecado;
	MateriaHasUsuarioRepository materiahasusuario;
	NotaRepository nota;
	RecadoRepository recado;
	RecadoHasUsuarioRepository recadohasusuario;
	UsuarioRepository usuario;
public:
	Repository();

	void open(const std::string& connectStringDataBase);
	template<class R, class T> R select(const T& obj);
	template<class T> T select(const string& where="");
	template<class T> int insert(const T& obj);
	template<class T> void update(const T& obj);
	template<class T> void update(const T& oldObj, const T& newObj);
	template<class T> void remove(const T& obj);

};

#endif // REPOSITORY_H

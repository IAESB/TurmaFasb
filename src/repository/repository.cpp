#include "repository.h"
Repository::Repository() :materia(dataBase) ,materiahasrecado(dataBase) ,materiahasusuario(dataBase) ,nota(dataBase) ,recado(dataBase) ,recadohasusuario(dataBase) ,usuario(dataBase) 
{}
void Repository::open(const std::string& connectStringDataBase)
{
	if(connectStringDataBase.size())
		dataBase.open(connectStringDataBase);
	else
		throw runtime_error("connectStringDataBase is EMPTY, info a url to connect in data base");
}

template<> MateriaPtr Repository::select(const Materia& obj)
{
	return materia.select(obj);
}
template<> MateriaList Repository::select(const string& where)
{
	return materia.select(where);
}
template<> int Repository::insert(const Materia& obj)
{
	return materia.insert(obj);
}
template<> void Repository::update(const Materia& obj)
{
	materia.update(obj);
}
template<> void Repository::update(const Materia& oldObj, const Materia& newObj)
{
	materia.update(oldObj, newObj);
}
template<> void Repository::remove(const Materia& obj)
{
	materia.remove(obj);
}

template<> MateriaHasRecadoPtr Repository::select(const MateriaHasRecado& obj)
{
	return materiahasrecado.select(obj);
}
template<> MateriaHasRecadoList Repository::select(const string& where)
{
	return materiahasrecado.select(where);
}
template<> int Repository::insert(const MateriaHasRecado& obj)
{
	return materiahasrecado.insert(obj);
}
template<> void Repository::update(const MateriaHasRecado& obj)
{
	materiahasrecado.update(obj);
}
template<> void Repository::update(const MateriaHasRecado& oldObj, const MateriaHasRecado& newObj)
{
	materiahasrecado.update(oldObj, newObj);
}
template<> void Repository::remove(const MateriaHasRecado& obj)
{
	materiahasrecado.remove(obj);
}

template<> MateriaHasUsuarioPtr Repository::select(const MateriaHasUsuario& obj)
{
	return materiahasusuario.select(obj);
}
template<> MateriaHasUsuarioList Repository::select(const string& where)
{
	return materiahasusuario.select(where);
}
template<> int Repository::insert(const MateriaHasUsuario& obj)
{
	return materiahasusuario.insert(obj);
}
template<> void Repository::update(const MateriaHasUsuario& obj)
{
	materiahasusuario.update(obj);
}
template<> void Repository::update(const MateriaHasUsuario& oldObj, const MateriaHasUsuario& newObj)
{
	materiahasusuario.update(oldObj, newObj);
}
template<> void Repository::remove(const MateriaHasUsuario& obj)
{
	materiahasusuario.remove(obj);
}

template<> NotaPtr Repository::select(const Nota& obj)
{
	return nota.select(obj);
}
template<> NotaList Repository::select(const string& where)
{
	return nota.select(where);
}
template<> int Repository::insert(const Nota& obj)
{
	return nota.insert(obj);
}
template<> void Repository::update(const Nota& obj)
{
	nota.update(obj);
}
template<> void Repository::update(const Nota& oldObj, const Nota& newObj)
{
	nota.update(oldObj, newObj);
}
template<> void Repository::remove(const Nota& obj)
{
	nota.remove(obj);
}

template<> RecadoPtr Repository::select(const Recado& obj)
{
	return recado.select(obj);
}
template<> RecadoList Repository::select(const string& where)
{
	return recado.select(where);
}
template<> int Repository::insert(const Recado& obj)
{
	return recado.insert(obj);
}
template<> void Repository::update(const Recado& obj)
{
	recado.update(obj);
}
template<> void Repository::update(const Recado& oldObj, const Recado& newObj)
{
	recado.update(oldObj, newObj);
}
template<> void Repository::remove(const Recado& obj)
{
	recado.remove(obj);
}

template<> RecadoHasUsuarioPtr Repository::select(const RecadoHasUsuario& obj)
{
	return recadohasusuario.select(obj);
}
template<> RecadoHasUsuarioList Repository::select(const string& where)
{
	return recadohasusuario.select(where);
}
template<> int Repository::insert(const RecadoHasUsuario& obj)
{
	return recadohasusuario.insert(obj);
}
template<> void Repository::update(const RecadoHasUsuario& obj)
{
	recadohasusuario.update(obj);
}
template<> void Repository::update(const RecadoHasUsuario& oldObj, const RecadoHasUsuario& newObj)
{
	recadohasusuario.update(oldObj, newObj);
}
template<> void Repository::remove(const RecadoHasUsuario& obj)
{
	recadohasusuario.remove(obj);
}

template<> UsuarioPtr Repository::select(const Usuario& obj)
{
	return usuario.select(obj);
}
template<> UsuarioList Repository::select(const string& where)
{
	return usuario.select(where);
}
template<> int Repository::insert(const Usuario& obj)
{
	return usuario.insert(obj);
}
template<> void Repository::update(const Usuario& obj)
{
	usuario.update(obj);
}
template<> void Repository::update(const Usuario& oldObj, const Usuario& newObj)
{
	usuario.update(oldObj, newObj);
}
template<> void Repository::remove(const Usuario& obj)
{
	usuario.remove(obj);
}

#include "repository.h"
Repository::Repository() :arquivo(dataBase) ,materia(dataBase) ,materiahasusuario(dataBase) ,nota(dataBase) ,recado(dataBase) ,recadohasmateria(dataBase) ,recadohasusuario(dataBase) ,usuario(dataBase) 
{}
void Repository::open(const std::string& connectStringDataBase)
{
	if(connectStringDataBase.size())
		dataBase.open(connectStringDataBase);
	else
		throw runtime_error("connectStringDataBase is EMPTY, info a url to connect in data base");
}

template<> ArquivoPtr Repository::select(const Arquivo& obj)
{
	return arquivo.select(obj);
}
template<> ArquivoList Repository::select(const string& where)
{
	return arquivo.select(where);
}
template<> int Repository::insert(const Arquivo& obj)
{
	return arquivo.insert(obj);
}
template<> void Repository::update(const Arquivo& obj)
{
	arquivo.update(obj);
}
template<> void Repository::update(const Arquivo& oldObj, const Arquivo& newObj)
{
	arquivo.update(oldObj, newObj);
}
template<> void Repository::remove(const Arquivo& obj)
{
	arquivo.remove(obj);
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

template<> RecadoHasMateriaPtr Repository::select(const RecadoHasMateria& obj)
{
	return recadohasmateria.select(obj);
}
template<> RecadoHasMateriaList Repository::select(const string& where)
{
	return recadohasmateria.select(where);
}
template<> int Repository::insert(const RecadoHasMateria& obj)
{
	return recadohasmateria.insert(obj);
}
template<> void Repository::update(const RecadoHasMateria& obj)
{
	recadohasmateria.update(obj);
}
template<> void Repository::update(const RecadoHasMateria& oldObj, const RecadoHasMateria& newObj)
{
	recadohasmateria.update(oldObj, newObj);
}
template<> void Repository::remove(const RecadoHasMateria& obj)
{
	recadohasmateria.remove(obj);
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

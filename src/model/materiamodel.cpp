#include "materiamodel.h"

MateriaList MateriaModel::list(const string& where)
{
    return repository.select<MateriaList>(where);
}

MateriaHasUsuarioList MateriaModel::list(const UsuarioPtr &usuario)
{
    MateriaHasUsuarioList listMU = repository.select<MateriaHasUsuarioList>("materia_has_usuario.usuario_id = '"+to_string(usuario->getId())+"'");
    return listMU;
}

MateriaPtr MateriaModel::get(const Materia& obj)
{
	return repository.select<MateriaPtr>(obj);
}
int MateriaModel::save(Materia& obj)
{
	return repository.insert(obj);
}
void MateriaModel::update(Materia& obj)
{
	repository.update(obj);
}
void MateriaModel::update(Materia& oldObj, Materia& newObj)
{
	repository.update(oldObj, newObj);
}
void MateriaModel::remove(Materia& obj)
{
	repository.remove(obj);
}

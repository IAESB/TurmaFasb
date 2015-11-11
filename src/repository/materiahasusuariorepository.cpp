#include "materiahasusuariorepository.h"
#include "util.hpp"
MateriaHasUsuarioRepository::MateriaHasUsuarioRepository(soci::session& db) : dataBase(db)
{
}

MateriaHasUsuarioPtr MateriaHasUsuarioRepository::select(const MateriaHasUsuario& obj)
{
	soci::row row;
	MateriaHasUsuarioPtr materiahasusuario(new MateriaHasUsuario);
	dataBase << "SELECT  materia_has_usuario.materia_id as MateriaHasUsuario_materia, materia.id as Materia_id, materia.nome as Materia_nome, materia.codigo as Materia_codigo, materia.descricao as Materia_descricao, materia.usuario_id as Materia_usuario, usuario.id as Usuario_id, usuario.nome as Usuario_nome, usuario.email as Usuario_email, usuario.senha as Usuario_senha, usuario.matricula as Usuario_matricula, usuario.foto as Usuario_foto, materia_has_usuario.usuario_id as MateriaHasUsuario_usuario"
	" FROM materia_has_usuario "
	"LEFT OUTER JOIN materia ON(materia_has_usuario.materia_id=materia.id) "
	"LEFT OUTER JOIN usuario ON(materia.usuario_id=usuario.id) "
	"WHERE materia_has_usuario.materia_id = :MateriaHasUsuario_materia AND materia_has_usuario.usuario_id = :MateriaHasUsuario_usuario", into(row), use(obj);
	if(!dataBase.got_data())
		materiahasusuario.reset();
	else
		type_conversion<MateriaHasUsuario>::from_base(row, i_ok, *materiahasusuario);
	return materiahasusuario;
}
MateriaHasUsuarioList MateriaHasUsuarioRepository::select(const string& where)
{
	soci::rowset<row> rs = 	dataBase.prepare << "SELECT  materia_has_usuario.materia_id as MateriaHasUsuario_materia, materia.id as Materia_id, materia.nome as Materia_nome, materia.codigo as Materia_codigo, materia.descricao as Materia_descricao, materia.usuario_id as Materia_usuario, usuario.id as Usuario_id, usuario.nome as Usuario_nome, usuario.email as Usuario_email, usuario.senha as Usuario_senha, usuario.matricula as Usuario_matricula, usuario.foto as Usuario_foto, materia_has_usuario.usuario_id as MateriaHasUsuario_usuario "
	" FROM materia_has_usuario "
	"LEFT OUTER JOIN materia ON(materia_has_usuario.materia_id=materia.id) "
	"LEFT OUTER JOIN usuario ON(materia.usuario_id=usuario.id)" 
	<< (where.size()?" WHERE "+where:"");
	MateriaHasUsuarioList materiahasusuarioList;
	for(row& r: rs)
	{
		MateriaHasUsuarioPtr materiahasusuario(new MateriaHasUsuario);
		type_conversion<MateriaHasUsuario>::from_base(r, i_ok, *materiahasusuario);
		materiahasusuarioList.push_back(materiahasusuario);
	}
	return materiahasusuarioList;
}

int MateriaHasUsuarioRepository::insert(const MateriaHasUsuario& materiahasusuario)
{
	dataBase << "insert into materia_has_usuario(materia_id, usuario_id)\
values(:MateriaHasUsuario_materia, :MateriaHasUsuario_usuario)", use(materiahasusuario);
	int id=0;
	dataBase << "SELECT LAST_INSERT_ID()", soci::into(id);
	return id;
}

void MateriaHasUsuarioRepository::remove(const MateriaHasUsuario& materiahasusuario)
{
	dataBase << "DELETE from materia_has_usuario WHERE materia_id=:MateriaHasUsuario_materia AND usuario_id=:MateriaHasUsuario_usuario", use(materiahasusuario);
}

void MateriaHasUsuarioRepository::update(const MateriaHasUsuario& materiahasusuario)
{
	dataBase << "update materia_has_usuario set materia_id=:MateriaHasUsuario_materia, usuario_id=:MateriaHasUsuario_usuario WHERE materia_id=:MateriaHasUsuario_materia AND usuario_id=:MateriaHasUsuario_usuario", use(materiahasusuario);
}

void MateriaHasUsuarioRepository::update(const MateriaHasUsuario& oldObj, const MateriaHasUsuario& newObj)
{
	dataBase << "update materia_has_usuario set materia_id=:MateriaHasUsuario_materia, usuario_id=:MateriaHasUsuario_usuario WHERE materia_id='"<<oldObj.getMateria()->getId()<<"\'' AND usuario_id='"<<oldObj.getUsuario()->getId()<<"\'", use(newObj);
}


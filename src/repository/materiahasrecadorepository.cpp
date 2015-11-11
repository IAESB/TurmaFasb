#include "materiahasrecadorepository.h"
#include "util.hpp"
MateriaHasRecadoRepository::MateriaHasRecadoRepository(soci::session& db) : dataBase(db)
{
}

MateriaHasRecadoPtr MateriaHasRecadoRepository::select(const MateriaHasRecado& obj)
{
	soci::row row;
	MateriaHasRecadoPtr materiahasrecado(new MateriaHasRecado);
	dataBase << "SELECT  materia_has_recado.materia_id as MateriaHasRecado_materia, materia.id as Materia_id, materia.nome as Materia_nome, materia.codigo as Materia_codigo, materia.descricao as Materia_descricao, materia.usuario_id as Materia_usuario, usuario.id as Usuario_id, usuario.nome as Usuario_nome, usuario.email as Usuario_email, usuario.senha as Usuario_senha, usuario.matricula as Usuario_matricula, usuario.foto as Usuario_foto, materia_has_recado.recado_id as MateriaHasRecado_recado, recado.id as Recado_id, recado.texto as Recado_texto, recado.data as Recado_data, materia_has_recado.usuario_id as MateriaHasRecado_usuario"
	" FROM materia_has_recado "
	"LEFT OUTER JOIN materia ON(materia_has_recado.materia_id=materia.id) "
	"LEFT OUTER JOIN usuario ON(materia.usuario_id=usuario.id) "
	"LEFT OUTER JOIN recado ON(materia_has_recado.recado_id=recado.id) "
	"WHERE materia_has_recado.materia_id = :MateriaHasRecado_materia AND materia_has_recado.recado_id = :MateriaHasRecado_recado AND materia_has_recado.usuario_id = :MateriaHasRecado_usuario", into(row), use(obj);
	if(!dataBase.got_data())
		materiahasrecado.reset();
	else
		type_conversion<MateriaHasRecado>::from_base(row, i_ok, *materiahasrecado);
	return materiahasrecado;
}
MateriaHasRecadoList MateriaHasRecadoRepository::select(const string& where)
{
	soci::rowset<row> rs = 	dataBase.prepare << "SELECT  materia_has_recado.materia_id as MateriaHasRecado_materia, materia.id as Materia_id, materia.nome as Materia_nome, materia.codigo as Materia_codigo, materia.descricao as Materia_descricao, materia.usuario_id as Materia_usuario, usuario.id as Usuario_id, usuario.nome as Usuario_nome, usuario.email as Usuario_email, usuario.senha as Usuario_senha, usuario.matricula as Usuario_matricula, usuario.foto as Usuario_foto, materia_has_recado.recado_id as MateriaHasRecado_recado, recado.id as Recado_id, recado.texto as Recado_texto, recado.data as Recado_data, materia_has_recado.usuario_id as MateriaHasRecado_usuario "
	" FROM materia_has_recado "
	"LEFT OUTER JOIN materia ON(materia_has_recado.materia_id=materia.id) "
	"LEFT OUTER JOIN usuario ON(materia.usuario_id=usuario.id) "
	"LEFT OUTER JOIN recado ON(materia_has_recado.recado_id=recado.id)" 
	<< (where.size()?" WHERE "+where:"");
	MateriaHasRecadoList materiahasrecadoList;
	for(row& r: rs)
	{
		MateriaHasRecadoPtr materiahasrecado(new MateriaHasRecado);
		type_conversion<MateriaHasRecado>::from_base(r, i_ok, *materiahasrecado);
		materiahasrecadoList.push_back(materiahasrecado);
	}
	return materiahasrecadoList;
}

int MateriaHasRecadoRepository::insert(const MateriaHasRecado& materiahasrecado)
{
	dataBase << "insert into materia_has_recado(materia_id, recado_id, usuario_id)\
values(:MateriaHasRecado_materia, :MateriaHasRecado_recado, :MateriaHasRecado_usuario)", use(materiahasrecado);
	int id=0;
	dataBase << "SELECT LAST_INSERT_ID()", soci::into(id);
	return id;
}

void MateriaHasRecadoRepository::remove(const MateriaHasRecado& materiahasrecado)
{
	dataBase << "DELETE from materia_has_recado WHERE materia_id=:MateriaHasRecado_materia AND recado_id=:MateriaHasRecado_recado AND usuario_id=:MateriaHasRecado_usuario", use(materiahasrecado);
}

void MateriaHasRecadoRepository::update(const MateriaHasRecado& materiahasrecado)
{
	dataBase << "update materia_has_recado set materia_id=:MateriaHasRecado_materia, recado_id=:MateriaHasRecado_recado, usuario_id=:MateriaHasRecado_usuario WHERE materia_id=:MateriaHasRecado_materia AND recado_id=:MateriaHasRecado_recado AND usuario_id=:MateriaHasRecado_usuario", use(materiahasrecado);
}

void MateriaHasRecadoRepository::update(const MateriaHasRecado& oldObj, const MateriaHasRecado& newObj)
{
	dataBase << "update materia_has_recado set materia_id=:MateriaHasRecado_materia, recado_id=:MateriaHasRecado_recado, usuario_id=:MateriaHasRecado_usuario WHERE materia_id='"<<oldObj.getMateria()->getId()<<"\'' AND recado_id='"<<oldObj.getRecado()->getId()<<"\'' AND usuario_id='"<<oldObj.getUsuario()->getId()<<"\'", use(newObj);
}


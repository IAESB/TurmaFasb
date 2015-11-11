#include "materiarepository.h"
#include "util.hpp"
MateriaRepository::MateriaRepository(soci::session& db) : dataBase(db)
{
}

MateriaPtr MateriaRepository::select(const Materia& obj)
{
	soci::row row;
	MateriaPtr materia(new Materia);
	dataBase << "SELECT  materia.id as Materia_id, materia.nome as Materia_nome, materia.codigo as Materia_codigo, materia.descricao as Materia_descricao, materia.usuario_id as Materia_usuario, usuario.id as Usuario_id, usuario.nome as Usuario_nome, usuario.email as Usuario_email, usuario.senha as Usuario_senha, usuario.matricula as Usuario_matricula, usuario.foto as Usuario_foto"
	" FROM materia "
	"LEFT OUTER JOIN usuario ON(materia.usuario_id=usuario.id) "
	"WHERE materia.id = :Materia_id AND materia.usuario_id = :Materia_usuario", into(row), use(obj);
	if(!dataBase.got_data())
		materia.reset();
	else
		type_conversion<Materia>::from_base(row, i_ok, *materia);
	return materia;
}
MateriaList MateriaRepository::select(const string& where)
{
	soci::rowset<row> rs = 	dataBase.prepare << "SELECT  materia.id as Materia_id, materia.nome as Materia_nome, materia.codigo as Materia_codigo, materia.descricao as Materia_descricao, materia.usuario_id as Materia_usuario, usuario.id as Usuario_id, usuario.nome as Usuario_nome, usuario.email as Usuario_email, usuario.senha as Usuario_senha, usuario.matricula as Usuario_matricula, usuario.foto as Usuario_foto "
	" FROM materia "
	"LEFT OUTER JOIN usuario ON(materia.usuario_id=usuario.id)" 
	<< (where.size()?" WHERE "+where:"");
	MateriaList materiaList;
	for(row& r: rs)
	{
		MateriaPtr materia(new Materia);
		type_conversion<Materia>::from_base(r, i_ok, *materia);
		materiaList.push_back(materia);
	}
	return materiaList;
}

int MateriaRepository::insert(const Materia& materia)
{
	dataBase << "insert into materia(id, nome, codigo, descricao, usuario_id)\
values(:Materia_id, :Materia_nome, :Materia_codigo, :Materia_descricao, :Materia_usuario)", use(materia);
	int id=0;
	dataBase << "SELECT LAST_INSERT_ID()", soci::into(id);
	return id;
}

void MateriaRepository::remove(const Materia& materia)
{
	dataBase << "DELETE from materia WHERE id=:Materia_id AND usuario_id=:Materia_usuario", use(materia);
}

void MateriaRepository::update(const Materia& materia)
{
	dataBase << "update materia set nome=:Materia_nome, codigo=:Materia_codigo, descricao=:Materia_descricao, usuario_id=:Materia_usuario WHERE id=:Materia_id AND usuario_id=:Materia_usuario", use(materia);
}

void MateriaRepository::update(const Materia& oldObj, const Materia& newObj)
{
	dataBase << "update materia set nome=:Materia_nome, codigo=:Materia_codigo, descricao=:Materia_descricao, usuario_id=:Materia_usuario WHERE id='"<<oldObj.getId()<<"\'' AND usuario_id='"<<oldObj.getUsuario()->getId()<<"\'", use(newObj);
}


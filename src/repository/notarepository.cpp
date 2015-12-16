#include "notarepository.h"
NotaRepository::NotaRepository(soci::session& db) : dataBase(db)
{
}

NotaPtr NotaRepository::select(const Nota& obj)
{
	soci::row row;
	NotaPtr nota(new Nota);
	dataBase << "SELECT  nota.id as Nota_id, nota.materia_id as Nota_materia, materia.id as Materia_id, materia.nome as Materia_nome, materia.codigo as Materia_codigo, materia.descricao as Materia_descricao, materia.ano as Materia_ano, materia.semestre as Materia_semestre, materia.curso as Materia_curso, materia.usuario_id as Materia_usuario, usuario.id as Usuario_id, usuario.nome as Usuario_nome, usuario.login as Usuario_login, usuario.senha as Usuario_senha, usuario.matricula as Usuario_matricula, usuario.foto as Usuario_foto, nota.usuario_id as Nota_usuario, nota.valor as Nota_valor, nota.descricao as Nota_descricao"
	" FROM nota "
	"LEFT OUTER JOIN materia ON(nota.materia_id=materia.id) "
	"LEFT OUTER JOIN usuario ON(nota.usuario_id=usuario.id) "
	"WHERE nota.id = :Nota_id AND nota.materia_id = :Nota_materia AND nota.usuario_id = :Nota_usuario", into(row), use(obj);
	if(!dataBase.got_data())
		nota.reset();
	else
		type_conversion<Nota>::from_base(row, i_ok, *nota);
	return nota;
}
NotaList NotaRepository::select(const string& where)
{
	soci::rowset<row> rs = 	dataBase.prepare << "SELECT  nota.id as Nota_id, nota.materia_id as Nota_materia, materia.id as Materia_id, materia.nome as Materia_nome, materia.codigo as Materia_codigo, materia.descricao as Materia_descricao, materia.ano as Materia_ano, materia.semestre as Materia_semestre, materia.curso as Materia_curso, materia.usuario_id as Materia_usuario, usuario.id as Usuario_id, usuario.nome as Usuario_nome, usuario.login as Usuario_login, usuario.senha as Usuario_senha, usuario.matricula as Usuario_matricula, usuario.foto as Usuario_foto, nota.usuario_id as Nota_usuario, nota.valor as Nota_valor, nota.descricao as Nota_descricao "
	" FROM nota "
	"LEFT OUTER JOIN materia ON(nota.materia_id=materia.id) "
	"LEFT OUTER JOIN usuario ON(nota.usuario_id=usuario.id)" 
	<< (where.size()?" WHERE "+where:"");
	NotaList notaList;
	for(row& r: rs)
	{
		NotaPtr nota(new Nota);
		type_conversion<Nota>::from_base(r, i_ok, *nota);
		notaList.push_back(nota);
	}
	return notaList;
}

int NotaRepository::insert(const Nota& nota)
{
	dataBase << "insert into nota(id, materia_id, usuario_id, valor, descricao)\
values(:Nota_id, :Nota_materia, :Nota_usuario, :Nota_valor, :Nota_descricao)", use(nota);
	int id=0;
	dataBase << "SELECT LAST_INSERT_ID()", soci::into(id);
	return id;
}

void NotaRepository::remove(const Nota& nota)
{
	dataBase << "DELETE from nota WHERE id=:Nota_id AND materia_id=:Nota_materia AND usuario_id=:Nota_usuario", use(nota);
}

void NotaRepository::update(const Nota& nota)
{
	dataBase << "update nota set materia_id=:Nota_materia, usuario_id=:Nota_usuario, valor=:Nota_valor, descricao=:Nota_descricao WHERE id=:Nota_id", use(nota);
}

void NotaRepository::update(const Nota& oldObj, const Nota& newObj)
{
	dataBase << "update nota set materia_id=:Nota_materia, usuario_id=:Nota_usuario, valor=:Nota_valor, descricao=:Nota_descricao WHERE id='"<<oldObj.getId()<<"\'", use(newObj);
}


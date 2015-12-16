#include "recadohasmateriarepository.h"
RecadoHasMateriaRepository::RecadoHasMateriaRepository(soci::session& db) : dataBase(db)
{
}

RecadoHasMateriaPtr RecadoHasMateriaRepository::select(const RecadoHasMateria& obj)
{
	soci::row row;
	RecadoHasMateriaPtr recadohasmateria(new RecadoHasMateria);
	dataBase << "SELECT  recado_has_materia.materia_id as RecadoHasMateria_materia, materia.id as Materia_id, materia.nome as Materia_nome, materia.codigo as Materia_codigo, materia.descricao as Materia_descricao, materia.ano as Materia_ano, materia.semestre as Materia_semestre, materia.curso as Materia_curso, materia.usuario_id as Materia_usuario, usuario.id as Usuario_id, usuario.nome as Usuario_nome, usuario.login as Usuario_login, usuario.senha as Usuario_senha, usuario.matricula as Usuario_matricula, usuario.foto as Usuario_foto, recado_has_materia.recado_id as RecadoHasMateria_recado, recado.id as Recado_id, recado.texto as Recado_texto, recado.data as Recado_data, recado.recado_id as Recado_recado, recado_has_materia.usuario_id as RecadoHasMateria_usuario"
	" FROM recado_has_materia "
	"LEFT OUTER JOIN materia ON(recado_has_materia.materia_id=materia.id) "
	"LEFT OUTER JOIN recado ON(recado_has_materia.recado_id=recado.id) "
	"LEFT OUTER JOIN usuario ON(recado_has_materia.usuario_id=usuario.id) "
	"WHERE recado_has_materia.materia_id = :RecadoHasMateria_materia AND recado_has_materia.recado_id = :RecadoHasMateria_recado AND recado_has_materia.usuario_id = :RecadoHasMateria_usuario", into(row), use(obj);
	if(!dataBase.got_data())
		recadohasmateria.reset();
	else
		type_conversion<RecadoHasMateria>::from_base(row, i_ok, *recadohasmateria);
	return recadohasmateria;
}
RecadoHasMateriaList RecadoHasMateriaRepository::select(const string& where)
{
	soci::rowset<row> rs = 	dataBase.prepare << "SELECT  recado_has_materia.materia_id as RecadoHasMateria_materia, materia.id as Materia_id, materia.nome as Materia_nome, materia.codigo as Materia_codigo, materia.descricao as Materia_descricao, materia.ano as Materia_ano, materia.semestre as Materia_semestre, materia.curso as Materia_curso, materia.usuario_id as Materia_usuario, usuario.id as Usuario_id, usuario.nome as Usuario_nome, usuario.login as Usuario_login, usuario.senha as Usuario_senha, usuario.matricula as Usuario_matricula, usuario.foto as Usuario_foto, recado_has_materia.recado_id as RecadoHasMateria_recado, recado.id as Recado_id, recado.texto as Recado_texto, recado.data as Recado_data, recado.recado_id as Recado_recado, recado_has_materia.usuario_id as RecadoHasMateria_usuario "
	" FROM recado_has_materia "
	"LEFT OUTER JOIN materia ON(recado_has_materia.materia_id=materia.id) "
	"LEFT OUTER JOIN recado ON(recado_has_materia.recado_id=recado.id) "
	"LEFT OUTER JOIN usuario ON(recado_has_materia.usuario_id=usuario.id)" 
	<< (where.size()?" WHERE "+where:"");
	RecadoHasMateriaList recadohasmateriaList;
	for(row& r: rs)
	{
		RecadoHasMateriaPtr recadohasmateria(new RecadoHasMateria);
		type_conversion<RecadoHasMateria>::from_base(r, i_ok, *recadohasmateria);
		recadohasmateriaList.push_back(recadohasmateria);
	}
	return recadohasmateriaList;
}

int RecadoHasMateriaRepository::insert(const RecadoHasMateria& recadohasmateria)
{
	dataBase << "insert into recado_has_materia(materia_id, recado_id, usuario_id)\
values(:RecadoHasMateria_materia, :RecadoHasMateria_recado, :RecadoHasMateria_usuario)", use(recadohasmateria);
	int id=0;
	dataBase << "SELECT LAST_INSERT_ID()", soci::into(id);
	return id;
}

void RecadoHasMateriaRepository::remove(const RecadoHasMateria& recadohasmateria)
{
	dataBase << "DELETE from recado_has_materia WHERE materia_id=:RecadoHasMateria_materia AND recado_id=:RecadoHasMateria_recado AND usuario_id=:RecadoHasMateria_usuario", use(recadohasmateria);
}

void RecadoHasMateriaRepository::update(const RecadoHasMateria& recadohasmateria)
{
	dataBase << "update recado_has_materia set materia_id=:RecadoHasMateria_materia, recado_id=:RecadoHasMateria_recado, usuario_id=:RecadoHasMateria_usuario WHERE materia_id=:RecadoHasMateria_materia AND recado_id=:RecadoHasMateria_recado AND usuario_id=:RecadoHasMateria_usuario", use(recadohasmateria);
}

void RecadoHasMateriaRepository::update(const RecadoHasMateria& oldObj, const RecadoHasMateria& newObj)
{
	dataBase << "update recado_has_materia set materia_id=:RecadoHasMateria_materia, recado_id=:RecadoHasMateria_recado, usuario_id=:RecadoHasMateria_usuario WHERE materia_id='"<<oldObj.getMateria()->getId()<<"\'' AND recado_id='"<<oldObj.getRecado()->getId()<<"\'' AND usuario_id='"<<oldObj.getUsuario()->getId()<<"\'", use(newObj);
}


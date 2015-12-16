#include "arquivorepository.h"
ArquivoRepository::ArquivoRepository(soci::session& db) : dataBase(db)
{
}

ArquivoPtr ArquivoRepository::select(const Arquivo& obj)
{
	soci::row row;
	ArquivoPtr arquivo(new Arquivo);
	dataBase << "SELECT  arquivo.id as Arquivo_id, arquivo.path as Arquivo_path, arquivo.data as Arquivo_data, arquivo.materia_id as Arquivo_materia, materia.id as Materia_id, materia.nome as Materia_nome, materia.codigo as Materia_codigo, materia.descricao as Materia_descricao, materia.ano as Materia_ano, materia.semestre as Materia_semestre, materia.curso as Materia_curso, materia.usuario_id as Materia_usuario, usuario.id as Usuario_id, usuario.nome as Usuario_nome, usuario.login as Usuario_login, usuario.senha as Usuario_senha, usuario.matricula as Usuario_matricula, usuario.foto as Usuario_foto, arquivo.usuario_id as Arquivo_usuario"
	" FROM arquivo "
	"LEFT OUTER JOIN materia ON(arquivo.materia_id=materia.id) "
	"LEFT OUTER JOIN usuario ON(arquivo.usuario_id=usuario.id) "
	"WHERE arquivo.id = :Arquivo_id AND arquivo.materia_id = :Arquivo_materia AND arquivo.usuario_id = :Arquivo_usuario", into(row), use(obj);
	if(!dataBase.got_data())
		arquivo.reset();
	else
		type_conversion<Arquivo>::from_base(row, i_ok, *arquivo);
	return arquivo;
}
ArquivoList ArquivoRepository::select(const string& where)
{
	soci::rowset<row> rs = 	dataBase.prepare << "SELECT  arquivo.id as Arquivo_id, arquivo.path as Arquivo_path, arquivo.data as Arquivo_data, arquivo.materia_id as Arquivo_materia, materia.id as Materia_id, materia.nome as Materia_nome, materia.codigo as Materia_codigo, materia.descricao as Materia_descricao, materia.ano as Materia_ano, materia.semestre as Materia_semestre, materia.curso as Materia_curso, materia.usuario_id as Materia_usuario, usuario.id as Usuario_id, usuario.nome as Usuario_nome, usuario.login as Usuario_login, usuario.senha as Usuario_senha, usuario.matricula as Usuario_matricula, usuario.foto as Usuario_foto, arquivo.usuario_id as Arquivo_usuario "
	" FROM arquivo "
	"LEFT OUTER JOIN materia ON(arquivo.materia_id=materia.id) "
	"LEFT OUTER JOIN usuario ON(arquivo.usuario_id=usuario.id)" 
	<< (where.size()?" WHERE "+where:"");
	ArquivoList arquivoList;
	for(row& r: rs)
	{
		ArquivoPtr arquivo(new Arquivo);
		type_conversion<Arquivo>::from_base(r, i_ok, *arquivo);
		arquivoList.push_back(arquivo);
	}
	return arquivoList;
}

int ArquivoRepository::insert(const Arquivo& arquivo)
{
	dataBase << "insert into arquivo(id, path, data, materia_id, usuario_id)\
values(:Arquivo_id, :Arquivo_path, :Arquivo_data, :Arquivo_materia, :Arquivo_usuario)", use(arquivo);
	int id=0;
	dataBase << "SELECT LAST_INSERT_ID()", soci::into(id);
	return id;
}

void ArquivoRepository::remove(const Arquivo& arquivo)
{
	dataBase << "DELETE from arquivo WHERE id=:Arquivo_id AND materia_id=:Arquivo_materia AND usuario_id=:Arquivo_usuario", use(arquivo);
}

void ArquivoRepository::update(const Arquivo& arquivo)
{
	dataBase << "update arquivo set path=:Arquivo_path, data=:Arquivo_data, materia_id=:Arquivo_materia, usuario_id=:Arquivo_usuario WHERE id=:Arquivo_id", use(arquivo);
}

void ArquivoRepository::update(const Arquivo& oldObj, const Arquivo& newObj)
{
	dataBase << "update arquivo set path=:Arquivo_path, data=:Arquivo_data, materia_id=:Arquivo_materia, usuario_id=:Arquivo_usuario WHERE id='"<<oldObj.getId()<<"\'", use(newObj);
}


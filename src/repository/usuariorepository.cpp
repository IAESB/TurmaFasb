#include "usuariorepository.h"
#include "util.hpp"
UsuarioRepository::UsuarioRepository(soci::session& db) : dataBase(db)
{
}

UsuarioPtr UsuarioRepository::select(const Usuario& obj)
{
	soci::row row;
	UsuarioPtr usuario(new Usuario);
	dataBase << "SELECT  usuario.id as Usuario_id, usuario.nome as Usuario_nome, usuario.email as Usuario_email, usuario.senha as Usuario_senha, usuario.matricula as Usuario_matricula, usuario.foto as Usuario_foto"
	" FROM usuario "
	"WHERE usuario.id = :Usuario_id", into(row), use(obj);
	if(!dataBase.got_data())
		usuario.reset();
	else
		type_conversion<Usuario>::from_base(row, i_ok, *usuario);
	return usuario;
}
UsuarioList UsuarioRepository::select(const string& where)
{
	soci::rowset<row> rs = 	dataBase.prepare << "SELECT  usuario.id as Usuario_id, usuario.nome as Usuario_nome, usuario.email as Usuario_email, usuario.senha as Usuario_senha, usuario.matricula as Usuario_matricula, usuario.foto as Usuario_foto "
	" FROM usuario" 
	<< (where.size()?" WHERE "+where:"");
	UsuarioList usuarioList;
	for(row& r: rs)
	{
		UsuarioPtr usuario(new Usuario);
		type_conversion<Usuario>::from_base(r, i_ok, *usuario);
		usuarioList.push_back(usuario);
	}
	return usuarioList;
}

int UsuarioRepository::insert(const Usuario& usuario)
{
	dataBase << "insert into usuario(id, nome, email, senha, matricula, foto)\
values(:Usuario_id, :Usuario_nome, :Usuario_email, :Usuario_senha, :Usuario_matricula, :Usuario_foto)", use(usuario);
	int id=0;
	dataBase << "SELECT LAST_INSERT_ID()", soci::into(id);
	return id;
}

void UsuarioRepository::remove(const Usuario& usuario)
{
	dataBase << "DELETE from usuario WHERE id=:Usuario_id", use(usuario);
}

void UsuarioRepository::update(const Usuario& usuario)
{
	dataBase << "update usuario set nome=:Usuario_nome, email=:Usuario_email, senha=:Usuario_senha, matricula=:Usuario_matricula, foto=:Usuario_foto WHERE id=:Usuario_id", use(usuario);
}

void UsuarioRepository::update(const Usuario& oldObj, const Usuario& newObj)
{
	dataBase << "update usuario set nome=:Usuario_nome, email=:Usuario_email, senha=:Usuario_senha, matricula=:Usuario_matricula, foto=:Usuario_foto WHERE id='"<<oldObj.getId()<<"\'", use(newObj);
}


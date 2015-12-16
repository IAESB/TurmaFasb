#include "recadohasusuariorepository.h"
RecadoHasUsuarioRepository::RecadoHasUsuarioRepository(soci::session& db) : dataBase(db)
{
}

RecadoHasUsuarioPtr RecadoHasUsuarioRepository::select(const RecadoHasUsuario& obj)
{
	soci::row row;
	RecadoHasUsuarioPtr recadohasusuario(new RecadoHasUsuario);
	dataBase << "SELECT  recado_has_usuario.recado_id as RecadoHasUsuario_recado, recado.id as Recado_id, recado.texto as Recado_texto, recado.data as Recado_data, recado.recado_id as Recado_recado, recado_has_usuario.remetente_id as RecadoHasUsuario_remetente, usuario.id as Usuario_id, usuario.nome as Usuario_nome, usuario.login as Usuario_login, usuario.senha as Usuario_senha, usuario.matricula as Usuario_matricula, usuario.foto as Usuario_foto, recado_has_usuario.destinatario_id as RecadoHasUsuario_destinatario"
	" FROM recado_has_usuario "
	"LEFT OUTER JOIN recado ON(recado_has_usuario.recado_id=recado.id) "
	"LEFT OUTER JOIN usuario ON(recado_has_usuario.usuario_id=usuario.id) "
	"WHERE recado_has_usuario.recado_id = :RecadoHasUsuario_recado AND recado_has_usuario.remetente_id = :RecadoHasUsuario_remetente AND recado_has_usuario.destinatario_id = :RecadoHasUsuario_destinatario", into(row), use(obj);
	if(!dataBase.got_data())
		recadohasusuario.reset();
	else
		type_conversion<RecadoHasUsuario>::from_base(row, i_ok, *recadohasusuario);
	return recadohasusuario;
}
RecadoHasUsuarioList RecadoHasUsuarioRepository::select(const string& where)
{
	soci::rowset<row> rs = 	dataBase.prepare << "SELECT  recado_has_usuario.recado_id as RecadoHasUsuario_recado, recado.id as Recado_id, recado.texto as Recado_texto, recado.data as Recado_data, recado.recado_id as Recado_recado, recado_has_usuario.remetente_id as RecadoHasUsuario_remetente, usuario.id as Usuario_id, usuario.nome as Usuario_nome, usuario.login as Usuario_login, usuario.senha as Usuario_senha, usuario.matricula as Usuario_matricula, usuario.foto as Usuario_foto, recado_has_usuario.destinatario_id as RecadoHasUsuario_destinatario "
	" FROM recado_has_usuario "
	"LEFT OUTER JOIN recado ON(recado_has_usuario.recado_id=recado.id) "
	"LEFT OUTER JOIN usuario ON(recado_has_usuario.usuario_id=usuario.id)" 
	<< (where.size()?" WHERE "+where:"");
	RecadoHasUsuarioList recadohasusuarioList;
	for(row& r: rs)
	{
		RecadoHasUsuarioPtr recadohasusuario(new RecadoHasUsuario);
		type_conversion<RecadoHasUsuario>::from_base(r, i_ok, *recadohasusuario);
		recadohasusuarioList.push_back(recadohasusuario);
	}
	return recadohasusuarioList;
}

int RecadoHasUsuarioRepository::insert(const RecadoHasUsuario& recadohasusuario)
{
	dataBase << "insert into recado_has_usuario(recado_id, remetente_id, destinatario_id)\
values(:RecadoHasUsuario_recado, :RecadoHasUsuario_remetente, :RecadoHasUsuario_destinatario)", use(recadohasusuario);
	int id=0;
	dataBase << "SELECT LAST_INSERT_ID()", soci::into(id);
	return id;
}

void RecadoHasUsuarioRepository::remove(const RecadoHasUsuario& recadohasusuario)
{
	dataBase << "DELETE from recado_has_usuario WHERE recado_id=:RecadoHasUsuario_recado AND remetente_id=:RecadoHasUsuario_remetente AND destinatario_id=:RecadoHasUsuario_destinatario", use(recadohasusuario);
}

void RecadoHasUsuarioRepository::update(const RecadoHasUsuario& recadohasusuario)
{
	dataBase << "update recado_has_usuario set recado_id=:RecadoHasUsuario_recado, remetente_id=:RecadoHasUsuario_remetente, destinatario_id=:RecadoHasUsuario_destinatario WHERE recado_id=:RecadoHasUsuario_recado AND remetente_id=:RecadoHasUsuario_remetente AND destinatario_id=:RecadoHasUsuario_destinatario", use(recadohasusuario);
}

void RecadoHasUsuarioRepository::update(const RecadoHasUsuario& oldObj, const RecadoHasUsuario& newObj)
{
	dataBase << "update recado_has_usuario set recado_id=:RecadoHasUsuario_recado, remetente_id=:RecadoHasUsuario_remetente, destinatario_id=:RecadoHasUsuario_destinatario WHERE recado_id='"<<oldObj.getRecado()->getId()<<"\'' AND remetente_id='"<<oldObj.getRemetente()->getId()<<"\'' AND destinatario_id='"<<oldObj.getDestinatario()->getId()<<"\'", use(newObj);
}


#ifndef RECADOHASUSUARIOREPOSITORY_H
#define RECADOHASUSUARIOREPOSITORY_H

#include <iostream>
#include <memory>
#include <vector>
#include <soci/soci.h>
#include "recadorepository.h"
#include "usuariorepository.h"
#include "usuariorepository.h"
#include "entity/recadohasusuario.h"
using namespace soci;


class RecadoHasUsuarioRepository
{
	soci::session& dataBase;
public:
	RecadoHasUsuarioRepository(soci::session& dataBase);
	int insert(const RecadoHasUsuario& recadohasusuario);
	RecadoHasUsuarioPtr select(const RecadoHasUsuario& recadohasusuario);
	RecadoHasUsuarioList select(const string& where="");
	void update(const RecadoHasUsuario& recadohasusuario);
	void update(const RecadoHasUsuario& oldObj, const RecadoHasUsuario& newObj);
	void remove(const RecadoHasUsuario& recadohasusuario);
};

namespace soci
{
template<>
struct type_conversion<RecadoHasUsuario>
{
typedef values base_type;
	template<class T>	static void from_base(const T& v, const indicator& ind, RecadoHasUsuario & p)
	{
		if (v.get_indicator("RecadoHasUsuario_recado") != i_null){
			p.setRecado( RecadoPtr( new Recado(v.template get<int>("RecadoHasUsuario_recado")) ) );
			type_conversion<Recado>::from_base(v, i_ok, *p.getRecado() );
		}
		if (v.get_indicator("RecadoHasUsuario_remetente") != i_null){
			p.setRemetente( UsuarioPtr( new Usuario(v.template get<int>("RecadoHasUsuario_remetente")) ) );
			type_conversion<Usuario>::from_base(v, i_ok, *p.getRemetente() );
		}
		if (v.get_indicator("RecadoHasUsuario_destinatario") != i_null){
			p.setDestinatario( UsuarioPtr( new Usuario(v.template get<int>("RecadoHasUsuario_destinatario")) ) );
			type_conversion<Usuario>::from_base(v, i_ok, *p.getDestinatario() );
		}
	}
	static void to_base(const RecadoHasUsuario & p, values & v, indicator & ind)
	{
		if( p.getRecado() )
			v.set( "RecadoHasUsuario_recado", p.getRecado()->getId() );
		else
			v.set( "RecadoHasUsuario_recado", NULL, i_null);
		if( p.getRemetente() )
			v.set( "RecadoHasUsuario_remetente", p.getRemetente()->getId() );
		else
			v.set( "RecadoHasUsuario_remetente", NULL, i_null);
		if( p.getDestinatario() )
			v.set( "RecadoHasUsuario_destinatario", p.getDestinatario()->getId() );
		else
			v.set( "RecadoHasUsuario_destinatario", NULL, i_null);
		ind = i_ok;
	}
};
}

#endif // RECADOHASUSUARIOREPOSITORY_H

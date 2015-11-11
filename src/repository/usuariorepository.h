#ifndef USUARIOREPOSITORY_H
#define USUARIOREPOSITORY_H

#include <iostream>
#include <memory>
#include <vector>
#include <soci/soci.h>
#include "entity/usuario.h"
using namespace soci;


class UsuarioRepository
{
	soci::session& dataBase;
public:
	UsuarioRepository(soci::session& dataBase);
	int insert(const Usuario& usuario);
	UsuarioPtr select(const Usuario& usuario);
	UsuarioList select(const string& where="");
	void update(const Usuario& usuario);
	void update(const Usuario& oldObj, const Usuario& newObj);
	void remove(const Usuario& usuario);
};

namespace soci
{
template<>
struct type_conversion<Usuario>
{
typedef values base_type;
	template<class T>	static void from_base(const T& v, const indicator& ind, Usuario & p)
	{
		if (v.get_indicator("Usuario_id") != i_null){
			p.setId( v.template get<int>("Usuario_id" ) );
		}
		if (v.get_indicator("Usuario_nome") != i_null){
			p.setNome( v.template get<std::string>("Usuario_nome" ) );
		}
		if (v.get_indicator("Usuario_email") != i_null){
			p.setEmail( v.template get<std::string>("Usuario_email" ) );
		}
		if (v.get_indicator("Usuario_senha") != i_null){
			p.setSenha( v.template get<std::string>("Usuario_senha" ) );
		}
		if (v.get_indicator("Usuario_matricula") != i_null){
			p.setMatricula( v.template get<std::string>("Usuario_matricula" ) );
		}
		if (v.get_indicator("Usuario_foto") != i_null){
			p.setFoto( v.template get<std::string>("Usuario_foto" ) );
		}
	}
	static void to_base(const Usuario & p, values & v, indicator & ind)
	{
		v.set( "Usuario_id", p.getId() );
		v.set( "Usuario_nome", p.getNome() );
		v.set( "Usuario_email", p.getEmail() );
		v.set( "Usuario_senha", p.getSenha() );
		v.set( "Usuario_matricula", p.getMatricula() );
		v.set( "Usuario_foto", p.getFoto() );
		ind = i_ok;
	}
};
}

#endif // USUARIOREPOSITORY_H

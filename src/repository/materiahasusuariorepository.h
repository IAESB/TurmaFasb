#ifndef MATERIAHASUSUARIOREPOSITORY_H
#define MATERIAHASUSUARIOREPOSITORY_H

#include <iostream>
#include <memory>
#include <vector>
#include <soci/soci.h>
#include "materiarepository.h"
#include "usuariorepository.h"
#include "entity/materiahasusuario.h"
using namespace soci;


class MateriaHasUsuarioRepository
{
	soci::session& dataBase;
public:
	MateriaHasUsuarioRepository(soci::session& dataBase);
	int insert(const MateriaHasUsuario& materiahasusuario);
	MateriaHasUsuarioPtr select(const MateriaHasUsuario& materiahasusuario);
	MateriaHasUsuarioList select(const string& where="");
	void update(const MateriaHasUsuario& materiahasusuario);
	void update(const MateriaHasUsuario& oldObj, const MateriaHasUsuario& newObj);
	void remove(const MateriaHasUsuario& materiahasusuario);
};

namespace soci
{
template<>
struct type_conversion<MateriaHasUsuario>
{
typedef values base_type;
	template<class T>	static void from_base(const T& v, const indicator& ind, MateriaHasUsuario & p)
	{
		if (v.get_indicator("MateriaHasUsuario_materia") != i_null){
			p.setMateria( MateriaPtr( new Materia(v.template get<int>("MateriaHasUsuario_materia")) ) );
			type_conversion<Materia>::from_base(v, i_ok, *p.getMateria() );
		}
		if (v.get_indicator("MateriaHasUsuario_usuario") != i_null){
			p.setUsuario( UsuarioPtr( new Usuario(v.template get<int>("MateriaHasUsuario_usuario")) ) );
			type_conversion<Usuario>::from_base(v, i_ok, *p.getUsuario() );
		}
	}
	static void to_base(const MateriaHasUsuario & p, values & v, indicator & ind)
	{
		if( p.getMateria() )
			v.set( "MateriaHasUsuario_materia", p.getMateria()->getId() );
		else
			v.set( "MateriaHasUsuario_materia", NULL, i_null);
		if( p.getUsuario() )
			v.set( "MateriaHasUsuario_usuario", p.getUsuario()->getId() );
		else
			v.set( "MateriaHasUsuario_usuario", NULL, i_null);
		ind = i_ok;
	}
};
}

#endif // MATERIAHASUSUARIOREPOSITORY_H

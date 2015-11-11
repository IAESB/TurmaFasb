#ifndef MATERIAHASRECADOREPOSITORY_H
#define MATERIAHASRECADOREPOSITORY_H

#include <iostream>
#include <memory>
#include <vector>
#include <soci/soci.h>
#include "materiarepository.h"
#include "recadorepository.h"
#include "usuariorepository.h"
#include "entity/materiahasrecado.h"
using namespace soci;


class MateriaHasRecadoRepository
{
	soci::session& dataBase;
public:
	MateriaHasRecadoRepository(soci::session& dataBase);
	int insert(const MateriaHasRecado& materiahasrecado);
	MateriaHasRecadoPtr select(const MateriaHasRecado& materiahasrecado);
	MateriaHasRecadoList select(const string& where="");
	void update(const MateriaHasRecado& materiahasrecado);
	void update(const MateriaHasRecado& oldObj, const MateriaHasRecado& newObj);
	void remove(const MateriaHasRecado& materiahasrecado);
};

namespace soci
{
template<>
struct type_conversion<MateriaHasRecado>
{
typedef values base_type;
	template<class T>	static void from_base(const T& v, const indicator& ind, MateriaHasRecado & p)
	{
		if (v.get_indicator("MateriaHasRecado_materia") != i_null){
			p.setMateria( MateriaPtr( new Materia(v.template get<int>("MateriaHasRecado_materia")) ) );
			type_conversion<Materia>::from_base(v, i_ok, *p.getMateria() );
		}
		if (v.get_indicator("MateriaHasRecado_recado") != i_null){
			p.setRecado( RecadoPtr( new Recado(v.template get<int>("MateriaHasRecado_recado")) ) );
			type_conversion<Recado>::from_base(v, i_ok, *p.getRecado() );
		}
		if (v.get_indicator("MateriaHasRecado_usuario") != i_null){
			p.setUsuario( UsuarioPtr( new Usuario(v.template get<int>("MateriaHasRecado_usuario")) ) );
			type_conversion<Usuario>::from_base(v, i_ok, *p.getUsuario() );
		}
	}
	static void to_base(const MateriaHasRecado & p, values & v, indicator & ind)
	{
		if( p.getMateria() )
			v.set( "MateriaHasRecado_materia", p.getMateria()->getId() );
		else
			v.set( "MateriaHasRecado_materia", NULL, i_null);
		if( p.getRecado() )
			v.set( "MateriaHasRecado_recado", p.getRecado()->getId() );
		else
			v.set( "MateriaHasRecado_recado", NULL, i_null);
		if( p.getUsuario() )
			v.set( "MateriaHasRecado_usuario", p.getUsuario()->getId() );
		else
			v.set( "MateriaHasRecado_usuario", NULL, i_null);
		ind = i_ok;
	}
};
}

#endif // MATERIAHASRECADOREPOSITORY_H

#ifndef RECADOHASMATERIAREPOSITORY_H
#define RECADOHASMATERIAREPOSITORY_H

#include <iostream>
#include <memory>
#include <vector>
#include <soci/soci.h>
#include "materiarepository.h"
#include "recadorepository.h"
#include "usuariorepository.h"
#include "entity/recadohasmateria.h"
using namespace soci;


class RecadoHasMateriaRepository
{
	soci::session& dataBase;
public:
	RecadoHasMateriaRepository(soci::session& dataBase);
	int insert(const RecadoHasMateria& recadohasmateria);
	RecadoHasMateriaPtr select(const RecadoHasMateria& recadohasmateria);
	RecadoHasMateriaList select(const string& where="");
	void update(const RecadoHasMateria& recadohasmateria);
	void update(const RecadoHasMateria& oldObj, const RecadoHasMateria& newObj);
	void remove(const RecadoHasMateria& recadohasmateria);
};

namespace soci
{
template<>
struct type_conversion<RecadoHasMateria>
{
typedef values base_type;
	template<class T>	static void from_base(const T& v, const indicator& ind, RecadoHasMateria & p)
	{
		if (v.get_indicator("RecadoHasMateria_materia") != i_null){
			p.setMateria( MateriaPtr( new Materia(v.template get<int>("RecadoHasMateria_materia")) ) );
			type_conversion<Materia>::from_base(v, i_ok, *p.getMateria() );
		}
		if (v.get_indicator("RecadoHasMateria_recado") != i_null){
			p.setRecado( RecadoPtr( new Recado(v.template get<int>("RecadoHasMateria_recado")) ) );
			type_conversion<Recado>::from_base(v, i_ok, *p.getRecado() );
		}
		if (v.get_indicator("RecadoHasMateria_usuario") != i_null){
			p.setUsuario( UsuarioPtr( new Usuario(v.template get<int>("RecadoHasMateria_usuario")) ) );
			type_conversion<Usuario>::from_base(v, i_ok, *p.getUsuario() );
		}
	}
	static void to_base(const RecadoHasMateria & p, values & v, indicator & ind)
	{
		if( p.getMateria() )
			v.set( "RecadoHasMateria_materia", p.getMateria()->getId() );
		else
			v.set( "RecadoHasMateria_materia", NULL, i_null);
		if( p.getRecado() )
			v.set( "RecadoHasMateria_recado", p.getRecado()->getId() );
		else
			v.set( "RecadoHasMateria_recado", NULL, i_null);
		if( p.getUsuario() )
			v.set( "RecadoHasMateria_usuario", p.getUsuario()->getId() );
		else
			v.set( "RecadoHasMateria_usuario", NULL, i_null);
		ind = i_ok;
	}
};
}

#endif // RECADOHASMATERIAREPOSITORY_H

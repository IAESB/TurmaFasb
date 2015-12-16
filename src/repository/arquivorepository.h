#ifndef ARQUIVOREPOSITORY_H
#define ARQUIVOREPOSITORY_H

#include <iostream>
#include <memory>
#include <vector>
#include <soci/soci.h>
#include "materiarepository.h"
#include "usuariorepository.h"
#include "entity/arquivo.h"
using namespace soci;


class ArquivoRepository
{
	soci::session& dataBase;
public:
	ArquivoRepository(soci::session& dataBase);
	int insert(const Arquivo& arquivo);
	ArquivoPtr select(const Arquivo& arquivo);
	ArquivoList select(const string& where="");
	void update(const Arquivo& arquivo);
	void update(const Arquivo& oldObj, const Arquivo& newObj);
	void remove(const Arquivo& arquivo);
};

namespace soci
{
template<>
struct type_conversion<Arquivo>
{
typedef values base_type;
	template<class T>	static void from_base(const T& v, const indicator& ind, Arquivo & p)
	{
		if (v.get_indicator("Arquivo_id") != i_null){
			p.setId( v.template get<int>("Arquivo_id" ) );
		}
		if (v.get_indicator("Arquivo_path") != i_null){
			p.setPath( v.template get<std::string>("Arquivo_path" ) );
		}
		if (v.get_indicator("Arquivo_data") != i_null){
			p.setData( v.template get<tm>("Arquivo_data" ) );
		}
		if (v.get_indicator("Arquivo_materia") != i_null){
			p.setMateria( MateriaPtr( new Materia(v.template get<int>("Arquivo_materia")) ) );
			type_conversion<Materia>::from_base(v, i_ok, *p.getMateria() );
		}
		if (v.get_indicator("Arquivo_usuario") != i_null){
			p.setUsuario( UsuarioPtr( new Usuario(v.template get<int>("Arquivo_usuario")) ) );
			type_conversion<Usuario>::from_base(v, i_ok, *p.getUsuario() );
		}
	}
	static void to_base(const Arquivo & p, values & v, indicator & ind)
	{
		v.set( "Arquivo_id", p.getId() );
		v.set( "Arquivo_path", p.getPath() );
		v.set( "Arquivo_data", p.getData() );
		if( p.getMateria() )
			v.set( "Arquivo_materia", p.getMateria()->getId() );
		else
			v.set( "Arquivo_materia", NULL, i_null);
		if( p.getUsuario() )
			v.set( "Arquivo_usuario", p.getUsuario()->getId() );
		else
			v.set( "Arquivo_usuario", NULL, i_null);
		ind = i_ok;
	}
};
}

#endif // ARQUIVOREPOSITORY_H

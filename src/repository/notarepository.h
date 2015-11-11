#ifndef NOTAREPOSITORY_H
#define NOTAREPOSITORY_H

#include <iostream>
#include <memory>
#include <vector>
#include <soci/soci.h>
#include "materiarepository.h"
#include "usuariorepository.h"
#include "entity/nota.h"
using namespace soci;


class NotaRepository
{
	soci::session& dataBase;
public:
	NotaRepository(soci::session& dataBase);
	int insert(const Nota& nota);
	NotaPtr select(const Nota& nota);
	NotaList select(const string& where="");
	void update(const Nota& nota);
	void update(const Nota& oldObj, const Nota& newObj);
	void remove(const Nota& nota);
};

namespace soci
{
template<>
struct type_conversion<Nota>
{
typedef values base_type;
	template<class T>	static void from_base(const T& v, const indicator& ind, Nota & p)
	{
		if (v.get_indicator("Nota_id") != i_null){
			p.setId( v.template get<int>("Nota_id" ) );
		}
		if (v.get_indicator("Nota_materia") != i_null){
			p.setMateria( MateriaPtr( new Materia(v.template get<int>("Nota_materia")) ) );
			type_conversion<Materia>::from_base(v, i_ok, *p.getMateria() );
		}
		if (v.get_indicator("Nota_usuario") != i_null){
			p.setUsuario( UsuarioPtr( new Usuario(v.template get<int>("Nota_usuario")) ) );
			type_conversion<Usuario>::from_base(v, i_ok, *p.getUsuario() );
		}
		if (v.get_indicator("Nota_valor") != i_null){
			p.setValor( v.template get<double>("Nota_valor" ) );
		}
		if (v.get_indicator("Nota_descicao") != i_null){
			p.setDescicao( v.template get<std::string>("Nota_descicao" ) );
		}
	}
	static void to_base(const Nota & p, values & v, indicator & ind)
	{
		v.set( "Nota_id", p.getId() );
		if( p.getMateria() )
			v.set( "Nota_materia", p.getMateria()->getId() );
		else
			v.set( "Nota_materia", NULL, i_null);
		if( p.getUsuario() )
			v.set( "Nota_usuario", p.getUsuario()->getId() );
		else
			v.set( "Nota_usuario", NULL, i_null);
		v.set( "Nota_valor", p.getValor() );
		v.set( "Nota_descicao", p.getDescicao() );
		ind = i_ok;
	}
};
}

#endif // NOTAREPOSITORY_H

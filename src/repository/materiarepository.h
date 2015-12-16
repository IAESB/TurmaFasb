#ifndef MATERIAREPOSITORY_H
#define MATERIAREPOSITORY_H

#include <iostream>
#include <memory>
#include <vector>
#include <soci/soci.h>
#include "usuariorepository.h"
#include "entity/materia.h"
using namespace soci;


class MateriaRepository
{
	soci::session& dataBase;
public:
	MateriaRepository(soci::session& dataBase);
	int insert(const Materia& materia);
	MateriaPtr select(const Materia& materia);
	MateriaList select(const string& where="");
	void update(const Materia& materia);
	void update(const Materia& oldObj, const Materia& newObj);
	void remove(const Materia& materia);
};

namespace soci
{
template<>
struct type_conversion<Materia>
{
typedef values base_type;
	template<class T>	static void from_base(const T& v, const indicator& ind, Materia & p)
	{
		if (v.get_indicator("Materia_id") != i_null){
			p.setId( v.template get<int>("Materia_id" ) );
		}
		if (v.get_indicator("Materia_nome") != i_null){
			p.setNome( v.template get<std::string>("Materia_nome" ) );
		}
		if (v.get_indicator("Materia_codigo") != i_null){
			p.setCodigo( v.template get<std::string>("Materia_codigo" ) );
		}
		if (v.get_indicator("Materia_descricao") != i_null){
			p.setDescricao( v.template get<std::string>("Materia_descricao" ) );
		}
		if (v.get_indicator("Materia_ano") != i_null){
			p.setAno( v.template get<int>("Materia_ano" ) );
		}
		if (v.get_indicator("Materia_semestre") != i_null){
			p.setSemestre( v.template get<int>("Materia_semestre" ) );
		}
		if (v.get_indicator("Materia_curso") != i_null){
			p.setCurso( v.template get<std::string>("Materia_curso" ) );
		}
		if (v.get_indicator("Materia_usuario") != i_null){
			p.setUsuario( UsuarioPtr( new Usuario(v.template get<int>("Materia_usuario")) ) );
			type_conversion<Usuario>::from_base(v, i_ok, *p.getUsuario() );
		}
	}
	static void to_base(const Materia & p, values & v, indicator & ind)
	{
		v.set( "Materia_id", p.getId() );
		v.set( "Materia_nome", p.getNome() );
		v.set( "Materia_codigo", p.getCodigo() );
		v.set( "Materia_descricao", p.getDescricao() );
		v.set( "Materia_ano", p.getAno() );
		v.set( "Materia_semestre", p.getSemestre() );
		v.set( "Materia_curso", p.getCurso() );
		if( p.getUsuario() )
			v.set( "Materia_usuario", p.getUsuario()->getId() );
		else
			v.set( "Materia_usuario", NULL, i_null);
		ind = i_ok;
	}
};
}

#endif // MATERIAREPOSITORY_H

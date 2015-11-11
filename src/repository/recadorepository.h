#ifndef RECADOREPOSITORY_H
#define RECADOREPOSITORY_H

#include <iostream>
#include <memory>
#include <vector>
#include <soci/soci.h>
#include "entity/recado.h"
using namespace soci;


class RecadoRepository
{
	soci::session& dataBase;
public:
	RecadoRepository(soci::session& dataBase);
	int insert(const Recado& recado);
	RecadoPtr select(const Recado& recado);
	RecadoList select(const string& where="");
	void update(const Recado& recado);
	void update(const Recado& oldObj, const Recado& newObj);
	void remove(const Recado& recado);
};

namespace soci
{
template<>
struct type_conversion<Recado>
{
typedef values base_type;
	template<class T>	static void from_base(const T& v, const indicator& ind, Recado & p)
	{
		if (v.get_indicator("Recado_id") != i_null){
			p.setId( v.template get<int>("Recado_id" ) );
		}
		if (v.get_indicator("Recado_texto") != i_null){
			p.setTexto( v.template get<std::string>("Recado_texto" ) );
		}
		if (v.get_indicator("Recado_data") != i_null){
			p.setData( v.template get<tm>("Recado_data" ) );
		}
	}
	static void to_base(const Recado & p, values & v, indicator & ind)
	{
		v.set( "Recado_id", p.getId() );
		v.set( "Recado_texto", p.getTexto() );
		v.set( "Recado_data", p.getData() );
		ind = i_ok;
	}
};
}

#endif // RECADOREPOSITORY_H

#include "recadorepository.h"
#include "util.hpp"
RecadoRepository::RecadoRepository(soci::session& db) : dataBase(db)
{
}

RecadoPtr RecadoRepository::select(const Recado& obj)
{
	soci::row row;
	RecadoPtr recado(new Recado);
	dataBase << "SELECT  recado.id as Recado_id, recado.texto as Recado_texto, recado.data as Recado_data"
	" FROM recado "
	"WHERE recado.id = :Recado_id", into(row), use(obj);
	if(!dataBase.got_data())
		recado.reset();
	else
		type_conversion<Recado>::from_base(row, i_ok, *recado);
	return recado;
}
RecadoList RecadoRepository::select(const string& where)
{
	soci::rowset<row> rs = 	dataBase.prepare << "SELECT  recado.id as Recado_id, recado.texto as Recado_texto, recado.data as Recado_data "
	" FROM recado" 
	<< (where.size()?" WHERE "+where:"");
	RecadoList recadoList;
	for(row& r: rs)
	{
		RecadoPtr recado(new Recado);
		type_conversion<Recado>::from_base(r, i_ok, *recado);
		recadoList.push_back(recado);
	}
	return recadoList;
}

int RecadoRepository::insert(const Recado& recado)
{
	dataBase << "insert into recado(id, texto, data)\
values(:Recado_id, :Recado_texto, :Recado_data)", use(recado);
	int id=0;
	dataBase << "SELECT LAST_INSERT_ID()", soci::into(id);
	return id;
}

void RecadoRepository::remove(const Recado& recado)
{
	dataBase << "DELETE from recado WHERE id=:Recado_id", use(recado);
}

void RecadoRepository::update(const Recado& recado)
{
	dataBase << "update recado set texto=:Recado_texto, data=:Recado_data WHERE id=:Recado_id", use(recado);
}

void RecadoRepository::update(const Recado& oldObj, const Recado& newObj)
{
	dataBase << "update recado set texto=:Recado_texto, data=:Recado_data WHERE id='"<<oldObj.getId()<<"\'", use(newObj);
}


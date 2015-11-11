#ifndef RECADO_H
#define RECADO_H

#include <iostream>
#include <memory>
#include <vector>

using namespace std;

class Recado;
typedef shared_ptr<Recado> RecadoPtr;
typedef vector<RecadoPtr> RecadoList;

class Recado
{
	int id; //key: PRI
	std::string texto;
	tm data;
public:
	Recado();
	Recado(int id);
	void init();
	int getId() const;
	void setId(int value);
	std::string getTexto() const;
	void setTexto(std::string value);
	tm getData() const;
	void setData(tm value);
};



#endif // RECADO_H

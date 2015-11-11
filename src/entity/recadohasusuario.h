#ifndef RECADOHASUSUARIO_H
#define RECADOHASUSUARIO_H

#include <iostream>
#include <memory>
#include <vector>
#include "recado.h"
#include "usuario.h"
#include "usuario.h"

using namespace std;

class RecadoHasUsuario;
typedef shared_ptr<RecadoHasUsuario> RecadoHasUsuarioPtr;
typedef vector<RecadoHasUsuarioPtr> RecadoHasUsuarioList;

class RecadoHasUsuario
{
	RecadoPtr recado; //key: PRI
	UsuarioPtr remetente; //key: PRI
	UsuarioPtr destinatario; //key: PRI
public:
	RecadoHasUsuario();
	RecadoHasUsuario(RecadoPtr recado, UsuarioPtr remetente, UsuarioPtr destinatario);
	void init();
	RecadoPtr getRecado() const;
	void setRecado(RecadoPtr value);
	UsuarioPtr getRemetente() const;
	void setRemetente(UsuarioPtr value);
	UsuarioPtr getDestinatario() const;
	void setDestinatario(UsuarioPtr value);
};



#endif // RECADOHASUSUARIO_H

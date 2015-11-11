#include "recadohasusuario.h"

RecadoHasUsuario::RecadoHasUsuario(){
	init();
}
RecadoHasUsuario::RecadoHasUsuario(RecadoPtr recado, UsuarioPtr remetente, UsuarioPtr destinatario)
{
	init();
	this->recado = recado;
	this->remetente = remetente;
	this->destinatario = destinatario;
}

void RecadoHasUsuario::init()
{
}
RecadoPtr RecadoHasUsuario::getRecado() const
{
	return recado;
}
void RecadoHasUsuario::setRecado(RecadoPtr value)
{
	recado = value;
}
UsuarioPtr RecadoHasUsuario::getRemetente() const
{
	return remetente;
}
void RecadoHasUsuario::setRemetente(UsuarioPtr value)
{
	remetente = value;
}
UsuarioPtr RecadoHasUsuario::getDestinatario() const
{
	return destinatario;
}
void RecadoHasUsuario::setDestinatario(UsuarioPtr value)
{
	destinatario = value;
}


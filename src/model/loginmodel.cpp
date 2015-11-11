#include "loginmodel.h"

LoginModel::LoginModel()
{

}

LoginModel::~LoginModel()
{

}

UsuarioPtr LoginModel::login(string email, string senha)
{
    UsuarioPtr usuario;
    UsuarioList usuarios = repository.select<UsuarioList>("email = '"+email+"' AND senha = '"+senha+"'");
    if( ! usuarios.empty())
        usuario = usuarios[0];

    return usuario;
}


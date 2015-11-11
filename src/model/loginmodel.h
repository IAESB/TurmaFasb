#ifndef LOGINMODEL_H
#define LOGINMODEL_H

#include "model.h"

class LoginModel : public Model
{
public:
    LoginModel();
    ~LoginModel();

    UsuarioPtr login(string email, string senha);
};

#endif // LOGINMODEL_H

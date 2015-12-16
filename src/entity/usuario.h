#ifndef USUARIO_H
#define USUARIO_H

#include <iostream>
#include <memory>
#include <vector>

using namespace std;

class Usuario;
typedef shared_ptr<Usuario> UsuarioPtr;
typedef vector<UsuarioPtr> UsuarioList;

class Usuario
{
	int id; //key: PRI
	std::string nome;
	std::string login;
	std::string senha;
	std::string matricula;
	std::string foto;
public:
	Usuario();
	Usuario(int id);
	void init();
	int getId() const;
	void setId(int value);
	std::string getNome() const;
	void setNome(std::string value);
	std::string getLogin() const;
	void setLogin(std::string value);
	std::string getSenha() const;
	void setSenha(std::string value);
	std::string getMatricula() const;
	void setMatricula(std::string value);
	std::string getFoto() const;
	void setFoto(std::string value);
};



#endif // USUARIO_H

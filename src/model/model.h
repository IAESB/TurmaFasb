#ifndef MODEL_H
#define MODEL_H

#include "repository/repository.h"

using namespace std;
class Model
{
public:
    static Repository repository;
	Model();
	void openRepository(const string& url);};

#endif // Controlador_H

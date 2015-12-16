#ifndef CONTROLLERBASE_H
#define CONTROLLERBASE_H

#include <mongoose/WebController.h>
#include <mongoose/Server.h>
#include <utilcpp/util.hpp>

using namespace std;
using namespace Mongoose;

class ControllerBase : public WebController
{
public:
	ControllerBase();
    void redirecionar(StreamResponse& response, const string& local);
};

#endif // Controlador_H

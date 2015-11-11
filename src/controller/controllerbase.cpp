#include "controllerbase.h"

ControllerBase::ControllerBase()
{
}

void ControllerBase::redirecionar(StreamResponse& response, const string& local)
{
	response.setCode(301);
	response.setHeader("Location", local);
}


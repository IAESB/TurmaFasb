#ifndef RECADOCONTROLLER_H
#define RECADOCONTROLLER_H

#include "controllerbase.h"
#include "model/recadomodel.h"

class RecadoController : public ControllerBase
{
    RecadoModel model;
public:
    RecadoController();
    ~RecadoController();
    void save(Request &request, StreamResponse &response);
    void list(Request &request, StreamResponse &response);
    void setup();
    static RecadoPtr request2recado(Request& request);
};

#endif // RECADOCONTROLLER_H

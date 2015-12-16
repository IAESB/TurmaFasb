#ifndef ARQUIVOCONTROLLER_H
#define ARQUIVOCONTROLLER_H

#include "controllerbase.h"
#include "model/arquivomodel.h"

class ArquivoController : public ControllerBase
{
    ArquivoModel model;
    map<string, string> mapExtensaoMimeType;
public:
    ArquivoController();
    ~ArquivoController();
    void save(Request &request, StreamResponse &response);
    void list(Request &request, StreamResponse &response);
    void setup();
    void setDirStorage(string path);
};

#endif // ARQUIVOCONTROLLER_H

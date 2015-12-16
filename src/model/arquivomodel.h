#ifndef ARQUIVOMODEL_H
#define ARQUIVOMODEL_H

#include "model.h"

class ArquivoModel : public Model
{
    string pathDirStorage;
public:
    int save(UsuarioPtr& usuario, MateriaPtr &materia, string nomeFile, string conteudoFile);
    ArquivoList list(const string& materia_id);
    ArquivoModel();
    ~ArquivoModel();
    void setDirStorage(string pathDirStorage);
};

#endif // ARQUIVOMODEL_H

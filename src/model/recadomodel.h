#ifndef RECADOMODEL_H
#define RECADOMODEL_H

#include "model.h"

class RecadoModel : public Model
{
public:
    RecadoModel();
    ~RecadoModel();
    int save(RecadoPtr &recado, UsuarioPtr &usuario, MateriaPtr &materia);
    RecadoHasMateriaList list(const string& materia_id);
};

#endif // RECADOMODEL_H

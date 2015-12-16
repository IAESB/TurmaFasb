#include "recadomodel.h"

RecadoModel::RecadoModel()
{

}

RecadoModel::~RecadoModel()
{

}

int RecadoModel::save(RecadoPtr& recado, UsuarioPtr& usuario, MateriaPtr& materia)
{
    recado->setId( repository.insert(*recado) );
    RecadoHasMateria materiaHasRecado;
    materiaHasRecado.setMateria(materia);
    materiaHasRecado.setRecado(recado);
    materiaHasRecado.setUsuario(usuario);
    repository.insert(materiaHasRecado);

    return recado->getId();
}

RecadoHasMateriaList RecadoModel::list(const string &materia_id)
{
    return repository.select<RecadoHasMateriaList>("recado_has_materia.materia_id="+materia_id);
}



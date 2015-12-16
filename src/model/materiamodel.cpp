#include "materiamodel.h"

MateriaList MateriaModel::list(const string& where)
{
    return repository.select<MateriaList>(where);
}

MateriaHasUsuarioList MateriaModel::list(const UsuarioPtr &usuario)
{
    MateriaHasUsuarioList listMU = repository.select<MateriaHasUsuarioList>("materia_has_usuario.usuario_id = '"+to_string(usuario->getId())+"'");
    return listMU;
}

MateriaPtr MateriaModel::get(const Materia& obj)
{
	return repository.select<MateriaPtr>(obj);
}
int MateriaModel::save(Materia& obj)
{
	return repository.insert(obj);
}
void MateriaModel::update(Materia& obj)
{
	repository.update(obj);
}
void MateriaModel::update(Materia& oldObj, Materia& newObj)
{
	repository.update(oldObj, newObj);
}
void MateriaModel::remove(Materia& obj)
{
    repository.remove(obj);
}

NotaList MateriaModel::notas(string &materia_id, UsuarioPtr &usuario)
{
    return repository.select<NotaList>("nota.materia_id="+materia_id+" AND nota.usuario_id="+to_string(usuario->getId()));
}

NotaList MateriaModel::medias(string &materia_id)
{
    return repository.select<NotaList>("nota.materia_id="+materia_id+" AND nota.usuario_id IS NULL");
}

NotaList MateriaModel::medias(UsuarioPtr &usuario)
{
    MateriaHasUsuarioList matriculas = list(usuario);
    string materia_id;
    NotaList result;
    double media=0;
    for(MateriaHasUsuarioPtr matricula: matriculas)
    {
        materia_id = to_string(matricula->getMateria()->getId());
        NotaPtr mediaTurma = this->media( materia_id );
        if(mediaTurma){
            mediaTurma->setMateria(matricula->getMateria());
            mediaTurma->setUsuario(matricula->getUsuario());
            mediaTurma->setDescricao("Turma Media");
            result.push_back(mediaTurma);

            media=0;
            NotaList notasList = notas(materia_id, usuario);
            for(int i=0; i<notasList.size();)
            {
                media=(media+notasList[i]->getValor())/++i;
            }
            NotaPtr mediaAluno(new Nota(0));
            mediaAluno->setValor(media);
            mediaAluno->setMateria(matricula->getMateria());
            mediaAluno->setUsuario(matricula->getUsuario());
            mediaAluno->setDescricao("Sua Media");
            result.push_back(mediaAluno);
        }
    }

    return result;
}

NotaPtr MateriaModel::media(string& materia_id)
{    
    NotaPtr retorno;
    NotaList notas = repository.select<NotaList>("nota.materia_id="+materia_id+" AND nota.usuario_id IS NULL AND nota.descricao = 'media total'");
    if(notas.size())
        retorno = notas[0];

    return retorno;
}

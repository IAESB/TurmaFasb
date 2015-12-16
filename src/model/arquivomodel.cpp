#include "arquivomodel.h"
#include <boost/filesystem.hpp>
#include <fstream>

int ArquivoModel::save(UsuarioPtr &usuario, MateriaPtr& materia, string nomeFile, string conteudoFile)
{
    int id=0;
    string path = pathDirStorage+to_string(materia->getId());
    boost::filesystem::create_directories(path);
    ofstream file(path+'/'+nomeFile ,ios::binary|ios::trunc);
    if(file.good())
    {
        file << conteudoFile;
        const time_t& now = time(NULL);
        Arquivo arquivo(0);
        arquivo.setData(*localtime(&now));
        arquivo.setMateria(materia);
        arquivo.setUsuario(usuario);
        arquivo.setPath(path);
        id = repository.insert(arquivo);
    }

    return id;
}

ArquivoList ArquivoModel::list(const string &materia_id)
{
    return repository.select<ArquivoList>("materia_id="+materia_id);
}

ArquivoModel::ArquivoModel()
{

}

ArquivoModel::~ArquivoModel()
{

}

void ArquivoModel::setDirStorage(string pathDirStorage)
{
    this->pathDirStorage = pathDirStorage;
}


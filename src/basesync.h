#ifndef BASESYNC_H
#define BASESYNC_H

#include "repository/repository.h"
#include "optionsargs.h"

class BaseSync
{
    Repository repository;
    soci::session odbc;
    map<int, Usuario> mapAluno;
    map<int, Usuario> mapProfessor;
    map<string, Materia> mapTurma;
public:
    BaseSync(const OptionsArgs& optrions);
    void init();
    ~BaseSync();
private:
    void insertAluno(soci::row& row);
    void insertProfessor(soci::row& row);
    void insertTurma(soci::row& row);
};

#endif // BASESYNC_H

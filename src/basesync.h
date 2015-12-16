#ifndef BASESYNC_H
#define BASESYNC_H

#include "repository/repository.h"
#include "optionsargs.h"

class BaseSync
{
    Repository repository;
    soci::session odbc;
    map<string, UsuarioPtr> mapAlunosExistentes;
    map<string, MateriaPtr> mapMateriasExistentes;
    map<int, NotaPtr> mapNotasExistentes;
    map<string, NotaPtr> mapMediaExistente;
    map<string, NotaPtr> mapMediaTotais;
    map<string, NotaPtr> mapMediaMentor;
    NotaList vecNotasMentor;
    MateriaHasUsuarioList vecMatriculaExistente;
    map<string, UsuarioPtr> mapAlunosMentor;
    map<string, MateriaPtr> mapMateriasMentor;
    map<string, map<string, MateriaHasUsuarioPtr> > matrizMateriaAluno;
    OptionsArgs optrions;
public:
    BaseSync(const OptionsArgs& optrions);
    void init();
    ~BaseSync();
private:
    soci::rowset<soci::row> carregaMateriaAlunos(int ano, int semestre);
    soci::rowset<soci::row> carregaNotas(int ano, int semestre);
    void carregaBaseExistente();
    void carregaBaseMentor();
    void mesclaMentorExistente();
    void insereDadosNovos();

    NotaPtr preencheNota(soci::row& row);
    UsuarioPtr preencheAluno(soci::row& row);
    UsuarioPtr preencheProfessor(soci::row& row);
    MateriaPtr preencheMateria(soci::row& row, UsuarioPtr &professor);
    void preencheMapMateriaAluno(MateriaPtr &materia, UsuarioPtr &aluno);
    void preencheMapNota(soci::row& row, NotaPtr &nota);
    void insertBanco();
    void insertBancoMateriaUsuario(MateriaPtr &materia, UsuarioPtr &usuario);
    void insertBancoNota(MateriaPtr &materia, UsuarioPtr &usuario);

};

#endif // BASESYNC_H

#include "basesync.h"

BaseSync::BaseSync(const OptionsArgs &optrions)
{
    odbc.open(optrions.mentor);
    repository.open(optrions.database);
}

void BaseSync::init()
{
    int ano = 2015;
    int semestre = 2;
    soci::rowset<row> rs = 	odbc.prepare << "SELECT DISTINCT "
            "MD_ANOMAT,MD_SEQMAT,CR_CODCUR, CR_NOMCUR, CR_HABILI, MD_FASDIS, DI_CODDIS, DI_DISTEL, DI_DESDIS,PF_CODPRO, PF_NOMPRO, MD_CODTUR, MD_CODGRA, AL_ALUTEL, AL_NOMALU "
            "FROM "
                "TB_CURSO, "
                "TB_GRADE, "
                "TB_MESTRE_DISCIPLINA, "
                "TB_DISCIPLINA "
                   "left outer join TB_GRADE_HORARIO_PROF on (DI_CODDIS = GP_CODDIS and GP_ANOMAT=" << ano << " AND GP_SEQMAT = " << semestre <<" ) "
                   "left outer JOIN TB_PROFESSOR on (GP_CODPRO = PF_CODPRO), "
                "TB_ALUNO "
            "WHERE "
                    "MD_ANOMAT = " << ano <<
                "AND MD_SEQMAT = " << semestre <<
                "AND MD_CODSIT = 1 "
                "AND CR_CODCUR = GD_CODCUR "
                "AND GD_CODGRA = MD_CODGRA "
                "AND MD_CODDIS = DI_CODDIS "
                "AND MD_CODALU = AL_CODALU "
                "AND MD_CODRES <> 16 "
            "ORDER BY "
                "MD_ANOMAT,MD_SEQMAT,MD_CODTUR, AL_NOMALU ";
}

BaseSync::~BaseSync()
{

}


#include "basesync.h"
#include <boost/algorithm/string.hpp>
#include <time.h>

BaseSync::BaseSync(const OptionsArgs &optrions)
{
    this->optrions = optrions;
    if( ! optrions.mentor.empty())
        odbc.open(optrions.mentor);
    repository.open(optrions.database);
}

BaseSync::~BaseSync()
{

}

void BaseSync::init()
{
    if( ! odbc.get_backend() )
        return;

    time_t t = time(NULL);
    clog << "Sincronia iniciada as: " << asctime(localtime(&t));clog.flush();

    carregaBaseExistente();
    carregaBaseMentor();
    mesclaMentorExistente();
    insereDadosNovos();

    t = time(NULL);
    clog << "Sincronia finalizada as: " << asctime(localtime(&t));clog.flush();
}

soci::rowset<row> BaseSync::carregaMateriaAlunos(int ano, int semestre)
{
    soci::rowset<row> set = odbc.prepare << "SELECT DISTINCT "
            "MD_ANOMAT, MD_SEQMAT, MD_FASDIS, MD_CODTUR, MD_CODGRA, "
            "CR_CODCUR, CR_NOMCUR, CR_HABILI, "
            "DI_CODDIS, DI_DISTEL, DI_DESDIS, "
            "PF_CODPRO, PF_NOMPRO, PF_NROCPF, "
            "AL_ALUTEL, AL_NOMALU, AL_NROCPF "
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

    return set;
}

soci::rowset<row> BaseSync::carregaNotas(int ano, int semestre)
{
    soci::rowset<row> set = odbc.prepare <<
        "select HI_SEQHIS, HI_CODING, AL_ALUTEL, AL_NOMALU, HI_ANOMAT, DI_DESDIS, DI_CODDIS, HI_SEQMAT, HI_CODGRA, "
                " HI_FASDIS, HI_CODTUR, HI_CODNOT, HI_NOTA, HI_MEDPAR, HI_FALTAS"
        " from tb_historico"
            " inner join TB_INGRESSO on (IN_CODING = HI_CODING)"
            " inner join TB_ALUNO on (IN_CODALU = AL_CODALU)"
            " inner join TB_DISCIPLINA on (HI_CODDIS = DI_CODDIS)"
        " where "
            " hi_anomat = " << ano <<
            " and HI_SEQMAT = " << semestre;

    return set;
}

void BaseSync::carregaBaseExistente()
{
    auto vecAlunosExistentes = repository.select<UsuarioList>();
    for(UsuarioPtr& aluno: vecAlunosExistentes)
        mapAlunosExistentes[aluno->getMatricula()] = aluno;
    clog << vecAlunosExistentes.size() << " alunos ja estão cadastradas.\n";clog.flush();

    auto vecMateriasExistentes = repository.select<MateriaList>();
    for(MateriaPtr& materia: vecMateriasExistentes)
        mapMateriasExistentes[materia->getNome()+materia->getCodigo()] = materia;
    clog << mapMateriasExistentes.size() << " materias ja estão cadastradas.\n";clog.flush();

    vecMatriculaExistente = repository.select<MateriaHasUsuarioList>();
    clog << vecMatriculaExistente.size() << " matricolas ja estão cadastradas.\n";clog.flush();

    auto vecNotas = repository.select<NotaList>();
    for(NotaPtr& nota: vecNotas)
    {
        mapNotasExistentes[nota->getId()] = nota;
        if( ! nota->getUsuario() ){
            const MateriaPtr& mat = nota->getMateria();
            mapMediaExistente[mat->getNome()+mat->getCodigo()+nota->getDescricao()] = nota;
        }
    }
    clog << vecNotas.size() << " notas ja estão cadastradas.\n";clog.flush();
}

void BaseSync::carregaBaseMentor()
{
    soci::rowset<row> set = carregaMateriaAlunos(optrions.ano, optrions.semestre);
    for(soci::row& row: set)
    {
        UsuarioPtr aluno = preencheAluno(row);
        mapAlunosMentor[aluno->getMatricula()] = aluno;

        UsuarioPtr professo = preencheProfessor(row);
        MateriaPtr materia = preencheMateria(row, professo);
        mapMateriasMentor[materia->getNome()+materia->getCodigo()] = materia;

        MateriaHasUsuarioPtr mu(new MateriaHasUsuario);
        mu->setMateria(materia);
        mu->setUsuario(aluno);
        matrizMateriaAluno[materia->getNome()+materia->getCodigo()][aluno->getMatricula()] = mu;
    }

    set = carregaNotas(optrions.ano, optrions.semestre);
    for(soci::row& row: set)
    {
        const string& matricula = boost::trim_copy(row.get<string>("AL_ALUTEL", ""));
        const string& codMateria = row.get<string>("DI_DESDIS", "")+row.get<string>("HI_CODTUR", "");

        NotaPtr nota = preencheNota(row);
        auto itM = mapMateriasMentor.find(codMateria);
        if(itM != mapMateriasMentor.end())
            nota->setMateria(itM->second);
        auto itA = mapAlunosMentor.find(matricula);
        if(itA != mapAlunosMentor.end())
            nota->setUsuario(itA->second);

        if(nota->getUsuario() && nota->getMateria())
            vecNotasMentor.push_back(nota);
        else
            cerr << "Nota com id: "<<nota->getId()<<" não foi encontrada um usuario ou uma materia.\n";

    }
}

void BaseSync::mesclaMentorExistente()
{
    for(auto& aluno: mapAlunosExistentes)
    {
        auto it = mapAlunosMentor.find(aluno.second->getMatricula());
        if(it != mapAlunosMentor.end())
        {
            it->second->setId(aluno.second->getId()); // seta esse ID para ser atualizado na Nota que tambem tiver esse ponteiro.
            mapAlunosMentor.erase(it);
        }
    }

    for(auto& materia: mapMateriasExistentes)
    {
        auto it = mapMateriasMentor.find(materia.second->getNome()+materia.second->getCodigo());
        if(it != mapMateriasMentor.end())
        {
            it->second->setId(materia.second->getId()); // seta esse ID para ser atualizado na Nota que tambem tiver esse ponteiro.
            mapMateriasMentor.erase(it);
        }
    }

    // Mesclando Matricula
    for(MateriaHasUsuarioPtr matricula: vecMatriculaExistente)
    {
        auto itM = matrizMateriaAluno.find(matricula->getMateria()->getNome()+matricula->getMateria()->getCodigo());
        if(itM != matrizMateriaAluno.end())
        {
            auto itA = itM->second.find(matricula->getUsuario()->getMatricula());
            if(itA != itM->second.end())
                itM->second.erase(itA);
            if(itM->second.empty())
                matrizMateriaAluno.erase(itM);
        }
    }

    // Esse for faz os pondeteiros da matriz apontar para os respctivos membros das maps
    for(auto& parM: matrizMateriaAluno)
    {
        for(auto& parA: parM.second)
        {
            MateriaHasUsuarioPtr mu = parA.second;
            auto itM = mapMateriasExistentes.find(mu->getMateria()->getNome()+mu->getMateria()->getCodigo());
            if(itM != mapMateriasExistentes.end())
                mu->setMateria(itM->second);
            else{
                itM = mapMateriasMentor.find(mu->getMateria()->getNome()+mu->getMateria()->getCodigo());
                if(itM != mapMateriasExistentes.end())
                    mu->setMateria(itM->second);
            }
            auto itA = mapAlunosExistentes.find(mu->getUsuario()->getMatricula());
            if(itA != mapAlunosExistentes.end())
                mu->setUsuario(itA->second);
            else{
                itA = mapAlunosMentor.find(mu->getUsuario()->getMatricula());
                if(itA != mapAlunosExistentes.end())
                    mu->setUsuario(itA->second);
            }
        }
    }
    // Fim Mesclando Matricula
}

void BaseSync::insereDadosNovos()
{
    clog << mapAlunosMentor.size() << " alunos novos serão inclusos\n";clog.flush();
    for(auto& par: mapAlunosMentor)
    {
        UsuarioPtr aluno = par.second;
        aluno->setId(repository.insert(*aluno));
    }

    clog << mapMateriasMentor.size() << " materias novas serão inclusos\n";clog.flush();
    for(auto& par: mapMateriasMentor)
    {
        MateriaPtr materia = par.second;
        UsuarioPtr professor = materia->getUsuario();
        auto itProf = mapAlunosExistentes.find(professor->getMatricula());
        if(itProf != mapAlunosExistentes.end())
            professor->setId(itProf->second->getId());
        else
            professor->setId(repository.insert(*professor));
        materia->setId(repository.insert(*materia));
    }

    for(auto& parM: matrizMateriaAluno)
    {
        clog << parM.second.size() << " matriculas novas sendo inclusas na materia "<<parM.first<<"\n";clog.flush();
        for(auto& parA: parM.second)
        {
            repository.insert(*parA.second);
        }
    }

    int cont=0;
    int ultimoPercent=-1;
    clog << "Atualizando "<<vecNotasMentor.size()<<" notas na base de dados";clog.flush();
    for(NotaPtr& nota: vecNotasMentor)
    {

        if(mapNotasExistentes.find(nota->getId()) == mapNotasExistentes.end())
            repository.insert(*nota);
        else
            repository.update(*nota);

        const MateriaPtr& mat = nota->getMateria();
        const string& key = mat->getNome()+mat->getCodigo()+nota->getDescricao();
        NotaPtr& media = mapMediaMentor[key];
        if(!media){
            media = NotaPtr(new Nota());
            media->setId(0);
            media->setValor(0);
            media->setMateria(mat);
            media->setDescricao("media de: "+nota->getDescricao());
            int percent = cont*100/vecNotasMentor.size();
            if(percent % 10==0 && percent!=ultimoPercent){
                clog << '.'; clog.flush();
                ultimoPercent = percent;
            }
        }
        media->setId(media->getId()+1); // o ID é usado como contador pra fazer a divisão na media.
        media->setValor(media->getValor()+nota->getValor());
        cont++;
    }

    clog << "\nAtualizando "<<mapMediaMentor.size()<<" Medias na base de dados\n";clog.flush();
    for(auto& par: mapMediaMentor)
    {
        NotaPtr& media = par.second;
        media->setValor(media->getValor()/media->getId()); // faz a divisão da media
        const MateriaPtr& mat = media->getMateria();
        const auto& it = mapMediaExistente.find(mat->getNome()+mat->getCodigo()+media->getDescricao());

        if(it != mapMediaExistente.end())
        {
            media->setId(it->second->getId());
            repository.update(*media);
        }
        else
        {
            media->setId(0);
            repository.insert(*media);
        }

        NotaPtr& mediaTotal = mapMediaTotais[mat->getNome()+mat->getCodigo()];
        if(!mediaTotal){
            mediaTotal = NotaPtr(new Nota());
            mediaTotal->setId(0);
            mediaTotal->setValor(0);
            mediaTotal->setMateria(mat);
            mediaTotal->setDescricao("media total");
        }
        mediaTotal->setId(mediaTotal->getId()+1);
        mediaTotal->setValor(mediaTotal->getValor()+media->getValor());
    }

    for(auto& par: mapMediaTotais)
    {
        NotaPtr& media = par.second;
        media->setValor(media->getValor()/media->getId()); // faz a divisão da media
        const MateriaPtr& mat = media->getMateria();
        const auto& it = mapMediaExistente.find(mat->getNome()+mat->getCodigo()+media->getDescricao());

        if(it != mapMediaExistente.end())
        {
            media->setId(it->second->getId());
            repository.update(*media);
        }
        else
        {
            media->setId(0);
            repository.insert(*media);
        }
    }
}

NotaPtr BaseSync::preencheNota(row &row)
{
    NotaPtr nota(new Nota);
    nota->setId(row.get<int>("HI_SEQHIS", 0));
    nota->setValor(row.get<double>("HI_MEDPAR", 0));
    nota->setDescricao(to_string(row.get<int>("HI_CODNOT", 0)));
    return nota;
}

UsuarioPtr BaseSync::preencheAluno(soci::row &row)
{
    UsuarioPtr aluno(new Usuario);
    aluno->setId(0);
    aluno->setNome(row.get<string>("AL_NOMALU", ""));
    aluno->setMatricula(boost::trim_copy(row.get<string>("AL_ALUTEL", "")));
    aluno->setLogin(aluno->getMatricula());
    aluno->setSenha(row.get<string>("AL_NROCPF", ""));

    return aluno;
}

UsuarioPtr BaseSync::preencheProfessor(soci::row &row)
{
    UsuarioPtr professor(new Usuario);
    professor->setId(0);
    professor->setMatricula(to_string(row.get<int>("PF_CODPRO", 0)));
    professor->setNome( row.get<string>("PF_NOMPRO", ""));
    professor->setLogin(to_string(row.get<int>("PF_CODPRO", 0)));
    professor->setSenha(row.get<string>("PF_NROCPF", ""));

    return professor;
}

MateriaPtr BaseSync::preencheMateria(soci::row &row, UsuarioPtr& professor)
{
    MateriaPtr materia(new Materia());
    materia->setId(0);
    materia->setNome(row.get<string>("DI_DESDIS"));
    materia->setCodigo(row.get<string>("MD_CODTUR"));
    materia->setAno(row.get<int>("MD_ANOMAT"));
    materia->setSemestre(row.get<int>("MD_SEQMAT"));
    materia->setUsuario(professor);
    return materia;
}

/*
void BaseSync::preencheMapNota(row &row, NotaPtr &nota)
{
    const string& matricula = boost::trim_left_copy(row.get<string>("AL_ALUTEL", ""));
    const string& codMateria = row.get<string>("HI_CODTUR", "");
    mapMateriaAlunoNota[codMateria][matricula].push_back(nota);
    mapIdNota[nota->getId()] = nota;
}

void BaseSync::insertBanco()
{
    int cont=0;
    for(auto& parMateriaAlunos: mapMateriaAluno)
    {
        auto itM = mapMateria.find(parMateriaAlunos.first);
        MateriaPtr materia;
        if(itM != mapMateria.end())
        {
            materia = itM->second;
            if(materia->getId() == 0){
                clog << "Inserindo "<<++cont<<" de "<<mapMateriaAluno.size()<<" materias...\n";clog.flush();
                UsuarioPtr professor = materia->getUsuario();
                professor->setId(repository.insert(*materia->getUsuario()));
                materia->setId(repository.insert(*materia));
            }
        }
        auto mapUsuario = parMateriaAlunos.second;
        int contU=0;
        clog << "inserindo e atualizando notas da materia "<<materia->getNome()<<"-"<<materia->getCodigo()<<" com "<<mapUsuario.size()<<" alunos.\n";
        for(auto& par: mapUsuario)
        {
            UsuarioPtr& usuario = par.second;
            if(usuario->getId() == 0)
            {
                clog << "Inserindo aluno "<<++contU<<" de "<<mapUsuario.size()<<endl;
                usuario->setId(repository.insert(*usuario));
            }
            insertBancoMateriaUsuario(materia, usuario);
            insertBancoNota(materia, usuario);
        }
    }
}

void BaseSync::insertBancoMateriaUsuario(MateriaPtr& materia, UsuarioPtr &usuario)
{
    bool matriculado = false;
    auto itI = matrizIdMateriaIdUsuario.find(materia->getId());
    if(itI != matrizIdMateriaIdUsuario.end())
    {
        auto itJ = itI->second.find(usuario->getId());
        if(itJ != itI->second.end())
        {
            matriculado = true;
        }
    }
    if(matriculado == false)
    {
        MateriaHasUsuario mu;
        mu.setMateria(materia);
        mu.setUsuario(usuario);
        repository.insert(mu);
    }
}

void BaseSync::insertBancoNota(MateriaPtr& materia, UsuarioPtr& usuario)
{
    auto it = mapMateriaAlunoNota.find(materia->getCodigo());
    if(it != mapMateriaAlunoNota.end())
    {
        auto it2 = it->second.find(usuario->getMatricula());
        if(it2 != it->second.end())
        {
            double media=0;
            const vector<NotaPtr>& vecNota = it2->second;
            for(NotaPtr nota: vecNota)
            {
                media += nota->getValor();
                nota->setMateria(materia);
                nota->setUsuario(usuario);
                if(mapIdNota.find(nota->getId()) != mapIdNota.end())
                    repository.update(*nota);
                else
                    repository.insert(*nota);
            }
            media=media/vecNota.size();
            Nota nota;
            nota.setId(0);
            nota.setMateria(materia);
            nota.setDescicao("Media da turma");
            nota.setValor(media);
        }
    }
    clog.flush();
}
*/

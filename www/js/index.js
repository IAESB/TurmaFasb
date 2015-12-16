

function initApp(){
    console.info("init app");
    verificaLogin();
    var materias = getListaMaterias();
    configuraGrafico(materias);
    preencheMenuMateria(materias);
}

function verificaLogin()
{
    var result = getDadosServidor("login/status");
    if(typeof(result) != "undefined" && ! result.logged ){
        window.location.href = "login.html";
    }
}

function getListaMaterias()
{
    var materias = [];
    var result = getDadosServidor("materia/list");
    if(result.success){
        materias = result.materias;
    }
    return materias;
}

function preencheMenuMateria(materias)
{
    for(var i in materias){
        var li = document.createElement("li");
        var a = document.createElement("a");
        a.textContent = materias[i].nome;
        a.href="materia.html?id="+materias[i].id;
        a.rel="external";
        a.className = "ui-btn ui-btn-icon-right ui-icon-carat-r";
        li.appendChild(a);
        $("#menuMaterias")[0].appendChild(li);
    }
}

function configuraGrafico(){
    
    var result = getDadosServidor("materia/list_medias");
    if(! result.success){
        return;
    }
    
    var options = {
        responsive:true,
    segmentShowStroke: false,
    animateRotate: true,
    animateScale: false,
    percentageInnerCutout: 50,
    tooltipTemplate: "<%= value %>%"
    };
    
    var labels = [];
    var suaMedia = [];
    var turmaMedias = [];
        
    var medias = result.medias;
    for(var i in medias)
    {
        labels[i] = medias[i].nome;
        if(labels[i].length>25){
            labels[i] = labels[i].substr(0, 25)+"...";
        }
        suaMedia[i] = medias[i].aluno;
        turmaMedias[i] = medias[i].turma;
    }

    var data = {
        labels: labels,
        datasets: [
            {
                label: "Sua Media",
                fillColor: "rgba(151,187,205, 0.7)",
                strokeColor: "rgba(151,187,205, 1)",
                pointColor: "rgba(151,187,205, 1)",
                pointStrokeColor: "#fff",
                pointHighlightFill: "#fff",
                pointHighlightStroke: "rgba(151,187,205, 1)",
                data: suaMedia
            },
            {
                label: "Media da Turma",
                fillColor: "rgba(220,220,220, 0.7)",
                strokeColor: "rgba(220,220,220, 1)",
                pointColor: "rgba(220,220,220, 1)",
                pointStrokeColor: "#fff",
                pointHighlightFill: "#fff",
                pointHighlightStroke: "rgba(220,220,220, 1)",
                data: turmaMedias
            }
        ]
    };
    var ctx = document.getElementById("graficoGeral").getContext("2d");
    var lineChart = new Chart(ctx).Bar(data, options);
    document.getElementById("legendaGrafico").innerHTML = lineChart.generateLegend();
}

$( document ).one( "pageshow", function() {
    initApp();
});
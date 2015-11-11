

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
    if( ! result.logged ){
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
        a.href="materia.html?id="+materias[i].id;
        a.rel="external";
        li.appendChild(a);
        $("#menuMaterias").append(li);
    }
}

function configuraGrafico(materias){
    
    var options = {
        responsive:true,
    segmentShowStroke: false,
    animateRotate: true,
    animateScale: false,
    percentageInnerCutout: 50,
    tooltipTemplate: "<%= value %>%"
    };

    var data = {
        labels: ["Materia1", "Materia2", "Materia3", "Materia4", "Materia5", "Materia6"],
        datasets: [
            {
                label: "Media da Turma",
                fillColor: "rgba(220,220,220, 0.7)",
                strokeColor: "rgba(220,220,220, 1)",
                pointColor: "rgba(220,220,220, 1)",
                pointStrokeColor: "#fff",
                pointHighlightFill: "#fff",
                pointHighlightStroke: "rgba(220,220,220,1)",
                data: [3.2, 9.0, 1.2, 6.5, 1.2, 3.9]
            },
            {
                label: "Sua Media",
                fillColor: "rgba(151,187,205, 0.7)",
                strokeColor: "rgba(151,187,205, 1)",
                pointColor: "rgba(151,187,205, 1)",
                pointStrokeColor: "#fff",
                pointHighlightFill: "#fff",
                pointHighlightStroke: "rgba(151,187,205,1)",
                data: [2.8, 10.0, 4.0, 6.9, 8.6, 7.7]
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
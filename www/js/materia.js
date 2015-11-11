$( document ).one( "pageshow", function() {
    initMateria();
});


function initMateria(){  
    console.info("init materia");    
    
    var bt = $(".btAdd");
    bt.on("click", function() {
        showHideAdd(bt);
    });
    
    configuraRecado();
    configuraEditor();
    configuraGrafico();
}

function configuraRecado(){
    $("#formAddRecado").on("submit", function(event){
        resultAddRecadoServer("foi");// apaga isso
        enviaFormulario($(this), resultAddRecadoServer);
        return false;
    });
}
                           
function resultAddRecadoServer(result){
    showHideAdd($("#btAddRecado"));
    var divUsuario = createDivUsuario(result);
    var divTexto = createDivTexto();
    var divRecado = document.createElement("div");
    divRecado.className ="recado";
    divRecado.appendChild(divUsuario);
    divRecado.appendChild(divTexto);
    var mural = document.querySelector(".mural");
    mural.insertBefore(divRecado, mural.firstChild)
}

function createDivUsuario(result){
    var div = document.createElement("div");
    var img = document.createElement("img");
    var labelNome = document.createElement("label");
    var labelData = document.createElement("label");
    div.className ="usuario";
    img.className ="avatar";
    img.src="imagens/avatar/user1.jpg";
    labelNome.className ="usuarioNome";
    labelNome.innerText="Fulano";
    labelData.className ="recadoData";
    labelData.innerText="23/09/2016";
    div.appendChild(img);
    div.appendChild(labelNome);
    div.appendChild(labelData);
    return div;
}
function createDivTexto(){
    var div = document.createElement("div");
    div.className="texto";
    var texto = CKEDITOR.instances.texto.getData();
    div.innerHTML = texto;
    CKEDITOR.instances.texto.setData("");
    return div;
}

function showHideAdd(button){
    var div = $(".add");
    div.slideToggle(function(){
        if(div.is(':visible')) {
            button.buttonMarkup({ icon: "delete" });
        }else{
            button.buttonMarkup({ icon: "plus"});
        } 
    });
}

function configuraGrafico()
{
    
    
    var options = {
        responsive:true,
        segmentShowStroke: false,
        animateRotate: true,
        animateScale: false,
        percentageInnerCutout: 50,
        tooltipTemplate: "<%= value %>%"
    };

    var data = {
        labels: ["Nota1", "Nota2", "Nota3"],
        datasets: [
            {
                label: "Media da Turma",
                fillColor: "rgba(220,220,220,0.2)",
                strokeColor: "rgba(220,220,220,1)",
                pointColor: "rgba(220,220,220,1)",
                pointStrokeColor: "#fff",
                pointHighlightFill: "#fff",
                pointHighlightStroke: "rgba(220,220,220,1)",
                data: [3.2, 9.0, 9.2]
            },
            {
                label: "Sua Nota",
                fillColor: "rgba(151,187,205,0.2)",
                strokeColor: "rgba(151,187,205,1)",
                pointColor: "rgba(151,187,205,1)",
                pointStrokeColor: "#fff",
                pointHighlightFill: "#fff",
                pointHighlightStroke: "rgba(151,187,205,1)",
                data: [2.8, 10.0, 8.0]
            }
        ]
    };


    var ctx = document.getElementById("graficoMateria").getContext("2d");
    var lineChart = new Chart(ctx).Line(data, options);
    document.getElementById("legendaGrafico").innerHTML = lineChart.generateLegend();
}

function configuraEditor()
{
     CKEDITOR.replace( 'texto' );
    
}

$( document ).one( "pageshow", function() {
    initMateria();
});


function initMateria(){  
    console.info("init materia");    
    
    var bt = $(".btAdd");
    bt.on("click", function() {
        showHideAdd(bt);
    });
    
    configuraGrafico();
    configuraRecado();
    configuraEditor();
    configuraArquivo();
}

function configuraArquivo()
{
    var materia_id = getParameterByName("id");
    var form = $("#formAddArquivo");
    form.submit(function( event ) {     
        var url = form[0].attributes.action.value + "&materia_id="+materia_id;
        var method = form[0].method;
        var formData = new FormData(form[0]);      
        resultAddArquivo(getDadosServidor(url, formData, method));
        return false; // cancel original event to prevent form submitting
    });
}

function resultAddArquivo(result)
{
    
}

function configuraRecado(){
    
    var listaRecado = getDadosServidor("recado/list", "materia_id="+getParameterByName("id"));
    if(listaRecado.success){
        var recados = listaRecado.recados;
        for(var i in listaRecado.recados)
        {
            addRecado(recados[i].data, recados[i].texto);
        }
    }
    
    $("#formAddRecado").on("submit", function(event){ 
        CKEDITOR.instances.texto.updateElement();
        var materia_id = $("#materia_id");
        materia_id.val(getParameterByName("id"));        
        var url = this.attributes.action.value;
        var method = this.method;
        var formData = $(this).serialize();        
        resultAddRecadoServer(getDadosServidor(url, formData, method));
        return false;
    });
}
                           
function resultAddRecadoServer(result){
    if(result.success){
        showHideAdd($("#btAddRecado"));
        var texto = CKEDITOR.instances.texto.getData();
        addRecado(result.data, texto);
        CKEDITOR.instances.texto.setData("");
    }
    else{
        alert(result.erro_msg);
    }
}

function addRecado(data, texto)
{
    var divUsuario = createDivUsuario(data);
    var divTexto = createDivTexto(texto);
    var divRecado = document.createElement("div");
    divRecado.className ="recado";
    divRecado.appendChild(divUsuario);
    divRecado.appendChild(divTexto);
    var mural = document.querySelector(".mural");
    mural.insertBefore(divRecado, mural.firstChild)
}

function createDivUsuario(data){
    var usuario = JSON.parse(localStorage.usuario);
    var div = document.createElement("div");
    var img = document.createElement("img");
    var labelNome = document.createElement("label");
    var labelData = document.createElement("label");
    
    div.className ="usuario";
    img.className ="avatar";
    img.src="imagens/avatar/user1.jpg";
    labelNome.className = "usuarioNome";
    labelNome.innerText = usuario.nome.split(' ')[0];
    labelData.className = "recadoData";
    labelData.innerText = data;
    div.appendChild(img);
    div.appendChild(labelNome);
    div.appendChild(labelData);
    return div;
}
function createDivTexto( texto ){
    var div = document.createElement("div");
    div.className="texto";
    div.innerHTML = texto;
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
    
    var id = getParameterByName("id");
    var notasMedias = getDadosServidor("materia/notas", {materia_id: id}, "GET");
    var labels = [];
    var notas = [];
    var medias = [];
    
    if(notasMedias.success){
        for(var i in notasMedias.notas)
        {
            notas[i] = notasMedias.notas[i].valor;
            labels[i] = notasMedias.notas[i].descricao;
            medias[i] = notasMedias.medias[i].valor;
        }
    }
    
    var options = {
        responsive: true,
        segmentShowStroke: false,
        animateRotate: true,
        animateScale: false,
        percentageInnerCutout: 50,
        tooltipTemplate: "<%= value %>%"
    };

    var data = {
        labels: labels,
        datasets: [
            {
                label: "Sua Nota",
                fillColor: "rgba(151,187,205,0.2)",
                strokeColor: "rgba(151,187,205,1)",
                pointColor: "rgba(151,187,205,1)",
                pointStrokeColor: "#fff",
                pointHighlightFill: "#fff",
                pointHighlightStroke: "rgba(151,187,205,1)",
                data: notas 
            },
            {
                label: "Media da Turma",
                fillColor: "rgba(220,220,220,0.2)",
                strokeColor: "rgba(220,220,220,1)",
                pointColor: "rgba(220,220,220,1)",
                pointStrokeColor: "#fff",
                pointHighlightFill: "#fff",
                pointHighlightStroke: "rgba(220,220,220,1)",
                data: medias
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

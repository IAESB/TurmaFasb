function enviaFormAjax(form, callBackSuccess, isFileUpload)
{
    
    if (typeof(isFileUpload) === "undefined"){ //test do parametro opcional
        isFileUpload = false;
    }
    
    form.submit(function( event ) {     
        var url = form[0].attributes.action.value;
        var method = form[0].method;
        var formData;
        if(isFileUpload){
            formData = new FormData(form[0]);  
        }else{
            formData = form.serialize();        
        }    
        callBackSuccess(getDadosServidor(url, formData, method));
        return false; // cancel original event to prevent form submitting
    });
}

function getDadosServidor(url, parametros, method)
{
    if(url.indexOf("http")<0){
        url = "http://"+window.location.host+"/"+url;
    }
    
    if (typeof(method) === "undefined"){//test do parametro opcional
        method = 'GET';
    }    
    
    var dados;
    $.ajax({url: url,
            data: parametros,
            type: method,                   
            async: false,
            dataType: 'json',
            beforeSend: function() {
                // This callback function will trigger before data is sent
                $.mobile.loading('show', {theme:"e", text:"Enviando...", textonly:false, textVisible: true}); // This will show ajax spinner
            },
            complete: function() {
                // This callback function will trigger on data sent/received complete
                $.mobile.loading('hide'); // This will hide ajax spinner
            },
            success: function (result) {
                  dados = result;  
            },
            error: function (request,error) {
                // This callback function will trigger on unsuccessful action                
                alert('Ocorreu um erro no envio, por favor tente novamente!');
            }
        }); 
    return dados;
}


function getParameterByName(name) {
    name = name.replace(/[\[]/, "\\[").replace(/[\]]/, "\\]");
    var regex = new RegExp("[\\?&]" + name + "=([^&#]*)"),
        results = regex.exec(location.search);
    return results === null ? "" : decodeURIComponent(results[1].replace(/\+/g, " "));
}
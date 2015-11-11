$( document ).one( "pagecreate", function() {    
    enviaFormAjax($("#formLoginAnunciante"), resultLoginAnunciante);
});

function resultLoginAnunciante(result)
{
    if(result.success) {
        window.location.href = "index.html";
    } else {
        $(".erro").slideDown("show");
    }   
}
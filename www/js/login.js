$( document ).one( "pagecreate", function() {    
    enviaFormAjax($("#formLoginAnunciante"), resultLogin);
    if(localStorage.usuario)
    {
        var usuario = JSON.parse(localStorage.usuario);
        var result = getDadosServidor("login", "login="+usuario.login+"&senha="+usuario.senha, "POST");
        resultLogin(result);
    }
});

function resultLogin(result)
{
    if(result.success) {
        localStorage.usuario = JSON.stringify(result.usuario);
        window.location.href = "index.html";
    } else {
        $(".erro").slideDown("show");
    }   
}
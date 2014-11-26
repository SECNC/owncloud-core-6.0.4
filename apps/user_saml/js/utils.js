(function() {
    
	var saml = document.createElement('script');
	saml.type = 'text/javascript';
	(document.getElementsByTagName('head')[0] || document.getElementsByTagName('body')[0]).appendChild(saml);
})();

$(document).ready(function(){

	var loginMsg = t('user_saml', 'Login com Federação');

    $('<div id="login-saml" style="display: inline"></div>').css({
		'text-align': 'rigth',
    }).appendTo('form');

    $('.wrapper').css({
    'width': '600px'

    })

    $('form').css({
    'width': 'inherit'

    })

    $('fieldset').css({
        'width': '100px' ,
        'display': 'none',
    'float': 'left',

    })

       $('head').append('<style type="text/css"> login{float: left; position: relative;} .push{float: left; position: relative;} a:link, a:visited { text-decoration: none    } a:hover {  text-decoration: none;     color: #ccc    }    a:active {    text-decoration: none    }</style>');

	$('<p>Selecione sua forma de acesso:</p></br>').css(
	{
        

		'text-align': 'center',
        'font-weight': 'bolder',
        'font-size' : '110%'
	}).appendTo('#login-saml');

    if ($('#user').val() == "") {
        $('#password').parent().hide();
        $('#remember_login').hide();
        $('#remember_login+label').hide();
        $('#submit').hide();
    }

    $('#user').change( function() {
        if ($(this).val() !== "") {
            $('#password').parent().show();
            $('#remember_login').show();
            $('#remember_login+label').show();
            $('#submit').show();
        }
        else {
            $('#password').parent().hide();
            $('#remember_login').hide();
            $('#remember_login+label').hide();
            $('#submit').hide();
        }
    });

	$('<a id="login-saml-action" href="?app=user_saml" ><div id="jatenho"><p>Já tenho uma conta</p></div></a>').css(
	{
		'text-align': 'center',
        'font-weight': 'bolder',
        'font-size' : '110%',
        'display' : 'inline',
        'float' : 'left',
        'width': '50%'
	}).appendTo('#login-saml');


    //$('<a id="login-saml-action" href="?app=user_saml" ></a>').css(
    //{
     //   'text-decoration': 'none'
    //}).appendTo('#jatenho');


  $('<a id="login-saml-action" href="/usuarios/solicitacao" ><div id="naotenho"><p>É o meu primeiro acesso</p></div></a>').css(
    {
        'text-align': 'center',
        'font-weight': 'bolder',
        'font-size' : '110%',
        'display' : 'inline',
        'width': '50%'
    }).appendTo('#login-saml');


	$('<img id="login-saml-img" src="' + OC.imagePath('user_saml', 'logo.png') + '" title="'+ loginMsg +'" alt="'+ loginMsg +'" />').css(
	{
		cursor : 'pointer',
        border : '1px solid #777'
	}).appendTo('#jatenho');




  

   // $('<a id="login-saml-action" href="?app=user_saml" ></a>').css(
  //  {
 //       'text-decoration': 'none'
//    }).appendTo('#login-saml');


    $('<img id="login-saml-img" src="' + OC.imagePath('user_saml', 'primeiro.png') + '" title="Primeira vez que aceso o serviço" alt="'+ loginMsg +'" />').css(
    {
        cursor : 'pointer',
        border : '1px solid #777'
    }).appendTo('#naotenho');





});

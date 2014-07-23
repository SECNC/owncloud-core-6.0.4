<?php
require_once __DIR__ . '/swiftAccess/action/Cotas.inc';

// Checa se o usuário está Logado
OCP\User::checkLoggedIn();


//Ler Mount.Json
$info = readData(false);

//Pega usuário da sessão
$user = OCP\User::getUser();

//Adiciona Dependencias
OCP\App::setActiveNavigationEntry( 'Cotas' );
OCP\Util::addScript('cotas', 'view'); 
OCP\Util::addStyle('cotas', 'cotas'); 

//Gera Pagina
$tmpl = new OCP\Template( 'cotas', 'main', 'user' );
$tmpl->assign( 'user', $user );
$tmpl->assign( 'info', $info );
$tmpl->printPage();

<?php
/* André Avelino da Silva Neto 06-08-2014 */
$isadmin = OC_User::isAdminUser(OC_User::getUser());
if ($isadmin){
OCP\App::addNavigationEntry( array( 
	'id' => 'gerencia_cotas',
	'order' => 100,
	'href' => OCP\Util::linkTo( 'gerencia_cotas', 'index.php' ),
	'icon' => OCP\Util::imagePath( 'gerencia_cotas', 'example.png' ),
	'name' => 'Definir cotas'
));
}

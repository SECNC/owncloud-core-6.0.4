<?php
/* André Avelino da Silva Neto 06-08-2014 
<a href="busca.php?user=<?php print($id); ?>">*/
//Checar se usuário é adm
set_include_path(get_include_path() . PATH_SEPARATOR .
        \OC_App::getAppPath('gerencia_cotas') . '/3rdparty');
require 'php-opencloud.php';
use OpenCloud\OpenStack;
use OpenCloud\Common\Constants\Size;

OC_Util::checkAdminUser();


$client = new OpenStack(OC_Config::getValue( "gtauth", 'http://endereco.com.br'), array(
    'username'   => OC_Config::getValue( "gtuser", 'usuario') ,
    'password'   => OC_Config::getValue( "gtsenha", 'senha'),
    'tenantName' => OC_Config::getValue( "gttenant", 'tenant')
));

$region = 'regionOne';
$objectStoreService = $client->objectStoreService('swift', $region);

$users = OC_User::getUsers();

foreach ($users as $user) {
	try{
	$container = $objectStoreService->getContainer($user);
	$usercota["$user"] = $container->getBytesQuota();
	}
	catch(Exception $e){
		$usercota["$user"] = -1;
	}
}

$usuario = $_POST["user"];

$tpl = new OCP\Template("gerencia_cotas", "result", "user");
$tpl->assign('result', 1 );
$tpl->assign('user', $usuario );
$tpl->assign('usercota', $usercota );
$tpl->assign('users', $users);
$tpl->printPage();

?>

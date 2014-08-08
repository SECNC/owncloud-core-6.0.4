<?php
/* André Avelino da Silva Neto 06-08-2014 
<a href="busca.php?user=<?php print($id); ?>">*/
require 'vendor/autoload.php';
use OpenCloud\OpenStack;
use OpenCloud\Common\Constants\Size;

$client = new OpenStack('http://192.168.1.80:5000/v2.0', array(
    'username'   => 'swift',
    'password'   => 'gtcnc',
    'tenantName' => 'service'
));

$region = 'regionOne';
$objectStoreService = $client->objectStoreService('swift', $region);

$users = OC_User::getUsers();

foreach ($users as $user) {
$container = $objectStoreService->getContainer($user);
$usercota["$user"] = $container->getBytesQuota();
}

$usuario = $_POST["user"];

$tpl = new OCP\Template("gerencia_cotas", "result", "user");
$tpl->assign('result', 1 );
$tpl->assign('user', $usuario );
$tpl->assign('usercota', $usercota );
$tpl->assign('users', $users);
$tpl->printPage();

?>

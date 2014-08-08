<?php
/* André Avelino da Silva Neto 06-08-2014 */

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

$novacota = $_POST["cota"];
$size = $_POST["size"];

session_start();
	foreach ($_SESSION['user'] as $uid){
		if (isset ($_POST["$uid"])){
			$user = $uid;
		}
	}
session_write_close();

if (strcmp($size,"MB") == 0){
	$cotacontainer = $novacota * Size::MB;
}else if (strcmp($size,"GB") == 0){
	$cotacontainer = $novacota * Size::GB;
}

$container = $objectStoreService->getContainer($user);
$container->setBytesQuota($cotacontainer);

$tmpl = new OCP\Template( 'gerencia_cotas', 'result', 'user' );
$tmpl->assign('result', 2);
$tmpl->printPage();

?>

<?php
/* André Avelino da Silva Neto 06-08-2014 */

//Checar se usuário é adm
set_include_path(get_include_path() . PATH_SEPARATOR .
        \OC_App::getAppPath('gerencia_cotas') . '/3rdparty');

require 'php-opencloud.php';

use OpenCloud\OpenStack;
use OpenCloud\Common\Constants\Size;

OC_Util::checkAdminUser();

$client = new OpenStack('https://200.129.132.69:5000/v2.0', array(
    'username'   => 'owncloud',
    'password'   => 'own123cloudSenha',
    'tenantName' => 'cnc'
));

$region = 'regionOne';
$objectStoreService = $client->objectStoreService('swift', $region);

$novacota = $_POST["cota"];
$size = $_POST["size"];

/*session_start();
	foreach ($_SESSION['user'] as $uid){
		if (isset ($_POST["$uid"])){
			$user = $uid;
		}
	}
session_write_close();
*/

$user = $_POST["uid"];

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

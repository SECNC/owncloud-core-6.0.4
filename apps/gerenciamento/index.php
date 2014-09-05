<?php //André Avelino da Silva Neto 28-08-2014

/*print_r (OC_Mount_Config::getSystemMountPoints());

$options = array ("user" => "swift", "bucket" => "mycont", "region" => "regionOne", "key" => "123", "tenant" => "service", "password" => "gtcnc", "service_name" => "swift", "url" => "http://192.168.1.80:5000/v2.0", "timeout" => "20" );

OC_Mount_Config::addMountPoint('adm', '\OC\Files\Storage\Swift', $options, 'user', $admin);

OC_Mount_Config::removeMountPoint('adm', 'user', $admin);

echo "HH";
*/

if (OC_User::isAdminUser(OC_User::getUser())){

require_once 'lib/access.php';

foreach (OC_Group::usersInGroup('inst_admin') as $inst){
	$instquota["$inst"] = OC_Gerencia::getInstDetails ($inst);
}

$tpl = new OCP\Template('gerenciamento', 'main', 'user');
$tpl->assign('instquota', $instquota);

if (!isset($_GET["ref"])){
$tpl->assign('ref', 'gerenciamento/');
}

$tpl->printPage();
}



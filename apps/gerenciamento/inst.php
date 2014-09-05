<?php //André Avelino da Silva Neto 28-08-2014

if (OC_Group::inGroup(OC_User::getUser(), 'inst_admin') || OC_User::isAdminUser(OC_User::getUser())){
require_once 'lib/access.php';


if (isset($_GET["inst"])){ 
	$inst = $_GET["inst"];
	
}else{
	$inst = OC_User::getUser();
}

session_start();
	$_SESSION['inst'] = $inst;
session_write_close();

$tpl = new OCP\Template('gerenciamento','usuarios','user');
$tpl->assign('inst', $inst);
$tpl->assign('userquota', OC_Gerencia::getUsersDetails($inst));
$tpl->assign('bytes', OC_Gerencia::getInstDetails($inst));
$tpl->printPage();
}

?>

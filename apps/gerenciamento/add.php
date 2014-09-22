<?php 

if (OC_Group::inGroup(OC_User::getUser(), 'inst_admin') || OC_User::isAdminUser(OC_User::getUser())){
require_once 'lib/access.php';

session_start();
	 $inst = $_SESSION['inst'];
session_write_close();


if (isset($_POST["newuser"])){
	if (strcmp($_POST["size"], "MB") == 0){
		$quota = $_POST["cota"] * 1024*1024;
	} else {
		$quota = $_POST["cota"] *1024*1024*1024;
	}

	OC_Gerencia::addUser($inst, $_POST["id"], $_POST["senha"], $quota);

	$tpl = new OCP\Template('gerenciamento','usuarios','user');
	$tpl->assign('inst', $inst);
	$tpl->assign('userquota', OC_Gerencia::getUsersDetails($inst));
	$tpl->assign('bytes', OC_Gerencia::getInstDetails($inst));
	$tpl->printPage();
	
} else {
	$tpl = new OCP\Template('gerenciamento','add','user');
	$tpl->printPage();
}
}


?>

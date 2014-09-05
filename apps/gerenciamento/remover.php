<?php //André Avelino da Silva Neto 28-08-2014

if (OC_Group::inGroup(OC_User::getUser(), 'inst_admin') || OC_User::isAdminUser(OC_User::getUser())){
require_once 'lib/access.php';

session_start();
	$inst = $_SESSION['inst'];
session_write_close();

$tpl = new OCP\Template('gerenciamento','usuarios','user');

if (isset($_POST["removeuser"])){
	if (strtolower($inst) == strtolower($_POST["uid"])){
		$tpl->assign('confirm', "n");
		$tpl->assign('msg', "Não é possível remover o usuário administrador!");

	} else {
		$tpl->assign('confirm', "y");
		$tpl->assign('usr', $_POST["uid"]);
	}
	
}


if (isset($_POST["sim"])){
	OC_Gerencia::removeUser ($inst, $_POST["uid"]);
	$tpl->assign('confirm', "n");
	$tpl->assign('msg',"Usuário(a) removido(a) com sucesso!");
} else if (isset($_POST["no"])){
	$tpl->assign('confirm', "n");
}


$tpl->assign('inst', $inst);
$tpl->assign('userquota', OC_Gerencia::getUsersDetails($inst));
$tpl->assign('bytes', OC_Gerencia::getInstDetails($inst));
$tpl->printPage();
}


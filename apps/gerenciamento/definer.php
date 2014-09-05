<?php //André Avelino da Silva Neto 28-08-2014

if (OC_Group::inGroup(OC_User::getUser(), 'inst_admin') || OC_User::isAdminUser(OC_User::getUser())){

require_once 'lib/access.php';

$user = $_POST["uid"];

$tpl = new OCP\Template('gerenciamento','usuarios','user');

session_start();
	 $inst = $_SESSION['inst'];
session_write_close();


if (preg_match("/^[0-9]+$/",$_POST["cota"])){

	if (strcmp($_POST["size"],"MB") == 0){
		$cota = $_POST["cota"] * (1024*1024);
	}else if (strcmp($_POST["size"],"GB") == 0){
		$cota = $_POST["cota"] * (1024*1024*1024);
	}

	if ($cota > (OC_Gerencia::getInstQuota($inst) - OC_Gerencia::getInstUsed($inst))){
		$tpl->assign('msg', "Não foi possível definir nova cota do(a) usuário(a) <b>$user</b>.<br>Ultrapassou a cota da instituição!");
	}else{
		OC_Gerencia::defineQuota($inst, $user, $cota);
		$tpl->assign('msg', "Nova cota do(a) usuário(a) <b>$user</b> definida com sucesso!");	
	}

} else {
	$tpl->assign('msg', 'Por favor insira um valor numérico para a cota');
}

$tpl->assign('inst', $inst);
$tpl->assign('userquota', OC_Gerencia::getUsersDetails($inst));
$tpl->assign('bytes', OC_Gerencia::getInstDetails($inst));
$tpl->printPage();
}
?>

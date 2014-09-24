<?php //André Avelino da Silva Neto 28-08-2014

require_once 'lib/access.php';

//OC_Preferences::setValue ('admin', 'gerenciamento', 'cotacontainer', OC_Gerencia::getUserQuotaRemain('service', 'admin'));
if (OC_User::isAdminUser(OC_User::getUser())){

	foreach (OC_Gerencia::getTenantsInfo() as $tenant => $data){
		$instquota[$tenant] = OC_Gerencia::getInstDetails ($tenant);
	}

	$tpl = new OCP\Template('gerenciamento', 'main', 'user');
	$tpl->assign('instquota', $instquota);

	if (!isset($_GET["ref"])){
		$tpl->assign('ref', 'gerenciamento/');
	}

$tpl->printPage();
}




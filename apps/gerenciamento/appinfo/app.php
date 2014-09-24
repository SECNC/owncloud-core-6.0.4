<?php
/* André Avelino da Silva Neto 06-08-2014 */

if (OC_User::isAdminUser(OC_User::getUser())){

	OCP\App::addNavigationEntry( array( 
		'id' => 'gerenciamento',
		'order' => 100,
		'href' => OCP\Util::linkTo('gerenciamento', 'index.php'),
		'icon' => OCP\Util::imagePath('gerenciamento', 'rename.svg'),
		'name' => 'Gerenciar'
	));

} else {

	if (OC_Group::inGroup(OC_User::getUser(), 'inst_admin')){
		OCP\App::addNavigationEntry( array( 
			'id' => 'gerenciamento',
			'order' => 100,
			'href' => OCP\Util::linkTo('gerenciamento', 'inst.php'),
			'icon' => OCP\Util::imagePath('gerenciamento', 'rename.svg'),
			'name' => 'Gerenciar'
		));
	}

}


	


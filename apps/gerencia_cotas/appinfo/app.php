<?php

OCP\App::addNavigationEntry( array( 
	'id' => 'gerencia_cotas',
	'order' => 100,
	'href' => OCP\Util::linkTo( 'gerencia_cotas', 'index.php' ),
	'icon' => OCP\Util::imagePath( 'gerencia_cotas', 'example.png' ),
	'name' => 'gerencia_cotas'
));

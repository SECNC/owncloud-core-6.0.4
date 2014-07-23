<?php

OCP\App::addNavigationEntry( array( 
	'id' => 'cotas',
	'order' => 100,
	'href' => OCP\Util::linkTo( 'cotas', 'index.php' ),
	'icon' => OCP\Util::imagePath( 'cotas', 'example.png' ),
	'name' => 'Cotas'
));

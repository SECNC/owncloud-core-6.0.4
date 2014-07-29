<?php

set_include_path(get_include_path() . PATH_SEPARATOR .
        \OC_App::getAppPath('gerencia_cotas') . '/3rdparty/rackspace-php-opencloud/lib');
require 'php-opencloud.php';

use \OpenCloud\Rackspace;
use \OpenCloud\ObjectStore\Constants\UrlType;


OC_User::setDisplayName('89aa4b196b48c8a13a6549bb1eaebd80@idp1.cafeexpresso.rnp.br', 'agoravai');
/*// 1. Instantiate a Rackspace client.
$client = new Rackspace(Rackspace::US_IDENTITY_ENDPOINT, array(
    'username' => getenv('RAX_USERNAME'),
    'apiKey'   => getenv('RAX_API_KEY')
));

// 2. Obtain an Object Store service object from the client.
$region = 'DFW';
$objectStoreService = $client->objectStoreService(null, $region);

// 3. Get container.
$container = $objectStoreService->getContainer('logos');

// 4. Get object.
$objectName = 'php-elephant.jpg';
$object = $container->getObject($objectName);

// 5. Get object's publicly-accessible iOS streaming URL.
$iosStreamingUrl = $object->getPublicUrl(UrlType::IOS_STREAMING);

printf("Object's publicly accessible iOS streaming URL: %s\n", $iosStreamingUrl);
*/

// Checa se o usuário está Logado
OCP\User::checkLoggedIn();



//Pega usuário da sessão
$user = OCP\User::getUser();

//Adiciona Dependencias
OCP\App::setActiveNavigationEntry( 'gerencia_cotas' );

//Gera Pagina
$tmpl = new OCP\Template( 'gerencia_cotas', 'main', 'user' );
$tmpl->assign( 'user', $user );
$tmpl->printPage();

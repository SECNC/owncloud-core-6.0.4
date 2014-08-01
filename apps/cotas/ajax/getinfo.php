<?php

require_once __DIR__ . '/../swiftAccess/action/authentication/ConnectionContext.inc';
require_once __DIR__ . '/../swiftAccess/action/authentication/KeystoneConnection.inc';
require_once __DIR__ . '/../swiftAccess/ResourceToolkit.inc';
require_once __DIR__ . '/../swiftAccess/action/Cotas.inc';

OCP\User::checkLoggedIn();
OCP\JSON::callCheck();

header("Content-Type: json/application");
$tenant = $_POST['tenant']; 
$user = $_POST['user']; 
$tipo = $_POST['tipo'];
$info = readData(false);

if($tipo == 0){
	$key = array_keys($info['user'][$user]);
	$tenantaws = getTenantInfos($info['user'][$user][$key[0]]['options']['tenant'],$info['user'][$user][$key[0]]['options']['password_encrypted'],$info['user'][$user][$key[0]]['options']['user'],$info['user'][$user][$key[0]]['options']['url'] . '/tokens');
}
else{
	$tenantaws = getTenantInfos($info['group'][$user]['/$user/files/' . $tenant]['options']['tenant'],$info['group'][$user]['/$user/files/' . $tenant]['options']['password_encrypted'],$info['group'][$user]['/$user/files/' . $tenant]['options']['user'],$info['group'][$user]['/$user/files/' . $tenant]['options']['url'] . '/tokens');
}

echo json_encode($tenantaws);
